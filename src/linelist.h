#ifndef LINELIST_H_
#define LINELIST_H_

#include <stddef.h>
#include <stdio.h>

// Node of the line list.
struct line_list_node_struct
{
        char * line;                            // Content of the line.
        struct line_list_node_struct * next;    // Pointer to the next node.
};

typedef struct line_list_node_struct line_list_node;

// List of lines.
struct line_list_struct
{
        line_list_node * first;  // Root node.
        line_list_node * last;   // Pointer to the last node for faster appending.
        size_t           size;   // Total number of nodes.
};

typedef struct line_list_struct line_list;

// Create a line list.
//
// The function initializes a new empty list.
int line_list_create(line_list ** list);

// Destroy a line list.
//
// The function destroys the content of the list
// (frees the lines, nodes, and the list itself).
int line_list_destroy(line_list ** list);

// Add line to the line list.
//
// The function adds a line to the list.
// The line is *not* copied but only grabs the pointer!
int line_list_add(line_list * list, char * line);

// Add stream to the line list.
int line_list_add_file(line_list * list, FILE * stream);

// All functions return 1 on success and 0 on failure.

#endif /* LINELIST_H_ */
