# specify the compiler
CC=gcc

# specify options for the compiler
CFLAGS=-c -Wall

all: compile_linked_list

compile_linked_list: linked_list.o
    $(CC) -o main linked_list.c

linked_list.o: main.cpp
    $(CC) $(CFLAGS) main.cpp

clean:
    rm -rf *o linked_list_binary
