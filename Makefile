CC = clang
CFLAGS = -Wall -Wextra -Werror -gdwarf-4

.PHONY: all clean
all: unique unittests

unique: unique.o tree.o
	$(CC) $(CFLAGS) unique.o tree.o -o unique

unittests: unittests.o tree.o
	$(CC) $(CFLAGS) unittests.o tree.o -o unittests

# Compile unique.c into an object file
unique.o: unique.c tree.h
	$(CC) $(CFLAGS) -c unique.c

# Compile tree.c into an object file
tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

# Compile unittests.c into an object file
unittests.o: unittests.c tree.h
	$(CC) $(CFLAGS) -c unittests.c

clean:
	rm -f *.o unique unittests