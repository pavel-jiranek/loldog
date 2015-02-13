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
