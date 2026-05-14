#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
* Purpose:      This is a recursive routine that prints a subtree
*               starting at a Node.  Usually it is not called directly,
*               but it is called by tree_print().
*
*               We use an "in-order" traversal of the tree.  This means
*               that the following order is followed:
*
*                   1. if node is NULL, then just return
*                   2. recurse to node->left
*                   3. print count and key of node
*                   4. recurse to node->right
*
*               When printing a Node, use the printf() format string
*               "%d %d\n".  The first number is the count of the Node;
*               the second number is the key of the Node.
*
* Paramter:     A pointer to the root node of the tree.
*
* Returns:      nothing
*/
void tree_print_node(Node *node) {
    assert(node);
    if (node->left != NULL) {
        tree_print_node(node->left); // opens entry to left subtree
    }

    printf("%d %d\n", node->count, node->key);

    if (node->right != NULL) { //opens entry to right subtree
        tree_print_node(node->right);
    }
}

/*
* Purpose:      Print a Tree by calling tree_print_node() with the
*               root node of the tree.
*
*               The value of tree->root might be NULL, in which case
*               the tree is empty and nothing is printed.
*
* Parameter:    Pointer to the Tree.
*
* Returns:      nothing
*/
void tree_print(Tree *tree) {
    assert(tree);
    if (tree->root != NULL) {
        tree_print_node(tree->root); //reoccurs
    }
}

/*
* Purpose:      Allocate a new (empty) tree.
*
*               Remember to use assert() to check that calloc() returns 
*               a non-NULL pointer.
*
* Parameters:   none
*
* Returns:      Pointer to a new Tree.
*/
Tree *tree_alloc(void) {
    Tree *t = calloc(1, sizeof(Tree));
    assert(t);
    return t;
}

/*
* Purpose:      This is the most important part of the Tree abstract
*               data type.
*
*               This function searches for the key, and then:
*               
*                 - If the key is IN THE TREE, then increment the count
*                   for that key.
*               
*                 - If the key is NOT IN THE TREE, then add it to the
*                   tree, and set its count to 1.
*               
*               See Section 2.2 of the assignment PDF for more information.
*
* Parameters:   tree    - Pointer to the Tree.
*               key     - The value to add to the Tree.
*
* Returns:      nothing
*/
void tree_add(Tree *tree, int key) {
    assert(tree); // starting at root, assert the spot in tree
    Node **p = &tree->root;

    // search down the tree
    while (*p != NULL) {
        //search for spot in tree
        if (key == (*p)->key) {
            (*p)->count++;
            return;
        } else if (key < (*p)->key) {
            //go left for smaller keys
            p = &((*p)->left);
        } else {
        // or right for larger keys
            p = &((*p)->right);
        }
    }

// At the null spot, we create a new node

    Node *n = calloc(1, sizeof(Node));
    assert(n);
    n->key = key;
    n->count = 1;
    n->left = NULL;
    n->right = NULL;

    *p = n;
}

/*
* Purpose:      This is a recursive routine that frees a subtree
*               starting at a node.  Usually it is not called
*               directly, but it is called by tree_free().
*
*               We use a "postorder" traversal of the tree to free all
*               of the nodes of the tree.  This means that the
*               following order is followed:
*
*                  1. if node is NULL, then just return.
*                  2. recurse to node->left
*                  3. recurse to node->right
*                  4. free the node
*
* Parameter:    Pointer to the root node of the tree.
*
* Returns:      nothing
*/
void tree_free_node(Node *node) {
    if (node == NULL) {
        return;
    }

    tree_free_node(node->left);
    tree_free_node(node->right);
    free(node);
}

/*
* Purpose:      Free a Tree that had been allocated by tree_alloc().
*
*                 1. If the tree pointer *p already is NULL, then the
*                    tree already has been freed, and so just return.
*                 2. Free the nodes of the tree by calling tree_free_node()
*                    with the root of the tree.
*                 3. Free the tree node by calling free(*p);
*                 4. Set the tree pointer to NULL:  *p = NULL;
*
* Parameter:    p  -  Pointer to a pointer to the node to be freed.
*/
void tree_free(Tree **p) {
    assert(p);
    if (*p == NULL) {
        return;
    }

    tree_free_node((*p)->root);
    free(*p);
    *p = NULL; // pointer set to null
}

/*
* Purpose:      Recursive routine for printing a debugging dump of a
*               binary tree.  Usually this routine is not called
*               directly, but it is called by tree_dump().
*
* Parameters:   node    - pointer to the root node of the tree
*               level   - indentation level
*               prefix  - char to print first:  <, /, or \
*
* Returns:      nothing
*/
void tree_dump_node(Node *node, int level, char prefix) {
    if (node) {
        tree_dump_node(node->right, level + 1, '/');
        printf("%*c %d (x%d)\n", 4 * level + 1, prefix, node->key,
                node->count);
        tree_dump_node(node->left, level + 1, '\\');
    } else {
        printf("%*c NULL\n", 4 * level + 1, prefix);
    }
}

/*
* Purpose:      Print debugging output by calling tree_dump_node() with
*               the root of the tree.
*
*               The result of calling this routine is a text-based image of
*               the tree that is printed sideways with the root on the
*               left.  For example, this is the debugging output for a tree
*               with 314 at the root, 76 to the left, and 95064 to the
*               right.  (Rotate your head to the left to see it with the
*               root at the top.)
*
*                                 / NULL
*                             / 95064 (x2)
*                                 \ NULL
*                         < 314 (x1)
*                                 / NULL
*                             \ 76 (x3)
*                                 \ NULL
*
* Parameter:    Pointer to the root node of the tree.
*
* Returns:      nothing
*/
void tree_dump(Tree *tree) {
    assert(tree);
    tree_dump_node(tree->root, 0, '<');
}

