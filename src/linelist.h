/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Pavel Jiranek <pavel.jiranek@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef LINELIST_H_
#define LINELIST_H_

#include <stddef.h>

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

// All functions return 1 on success and 0 on failure.

#endif /* LINELIST_H_ */
