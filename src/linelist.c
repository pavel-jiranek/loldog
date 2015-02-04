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

#include "linelist.h"

#include <stdlib.h>

#include "utils.h"

int line_list_create(line_list ** list)
{
    *list = malloc(sizeof(line_list));

    if (!list) return 0;

    (*list)->first = NULL;
    (*list)->last  = NULL;
    (*list)->size  = 0;

    return 1;
}

int line_list_destroy(line_list ** list)
{
    line_list_node * this = NULL, * next = NULL;
    this = (*list)->first;

    for ( ; this ; this = next)
    {
        next = this->next;
        free(this->line);
        free(this);
    }

    free(*list);

    *list = NULL;

    return 1;
}

int line_list_add(line_list * list, char * line)
{
    line_list_node * node = malloc(sizeof(line_list_node));

    if (!node) return 0;

    node->line = line;
    node->next = NULL;

    if (list->last)
    {
        list->last->next = node;
        list->last = node;
    }
    else
    {
        list->first = node;
        list->last  = node;
    }

    list->size++;

    return 1;
}

int line_list_add_file(line_list * list, FILE * stream)
{
    for ( ; ; )
    {
        // Get the line from the stream.
        size_t n;
        char * line = NULL;

        if (get_line(&line, &n, stream) < 0) break;

        // Append the line to the list or exit.
        if (!line_list_add(list, line)) return 0;
    }

    return 1;
}
