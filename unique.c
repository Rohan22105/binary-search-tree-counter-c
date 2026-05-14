#include "tree.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  unique NUM NUM NUM ...       (normal output)\n");
    printf("        unique -d NUM NUM NUM ...    (debugging output)\n");
    exit(0);
}


// Purpose: Checks if a given string is made up of only digits.
// Parameter: If any character is not a digit (like a letter or symbol), the program calls print_usage() and exits.
// returns usage, if digit doesn't appear

void check_number(const char *s) {
// paramter marking
//must be a digit, if not, show usage, and quit
    (void)s;  
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isdigit((unsigned char) s[i])) {
            print_usage();
        }
    }
}

//Purpose: The main program that processes command-line input.
// Parameters: argc and argv ( returns 0 for success)
//Return: normal mode and debug mode are outcome statements (0)

int main(int argc, char **argv) {
   (void)argc;  // for unused parameters
    (void)argv;  

    bool saw_debug = false; // tracks d-

    Tree *tree = tree_alloc();
    assert(tree);

 // Create an empty tree to store numbers.
    for (int i = 1; i < argc; i++) {

    //if user passed -d, then enable debug mode
        if (strcmp(argv[i], "-d") == 0) {
            saw_debug = true;
            continue;  
        }
     //check if valid number (digits only)
        check_number(argv[i]);
    // convert string to int value
        int value = atoi(argv[i]);
        tree_add(tree, value);
    }
// Print depending on the mode chosen.

    if (saw_debug) {
        tree_dump(tree);
    } else {
        tree_print(tree);
    }

    tree_free(&tree);

    return 0;
}
