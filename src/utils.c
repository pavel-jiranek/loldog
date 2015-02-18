#include "utils.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

ssize_t get_line(char ** line, size_t * n, FILE * stream)
{
    // TODO Currently, the tabs are read as tabs. Consequently, if the
    // TODO color changes with columns, the colors need not to be correct.
    // TODO We should fix this and replace tabs by some appropriate
    // TODO number of spaces.

    size_t const len_init = 128;

    char * buf = *line; // Get the buffer...
    size_t len = *n;    // ...and its length.

    // Allocate the initial buffer if not yet allocated.
    if (!buf)
    {
        buf = malloc(sizeof(char) * len_init);
        len = len_init;
    }

    // Return an error if the allocation failed.
    if (!buf)
    {
        *n = 0;
        return -1;
    }

    int ch;
    ssize_t i;
    char * ptr = buf;

    // Get characters from the stream until EOF or CR.
    for (i = 0; ; i++)
    {
        ch = fgetc(stream);

        // On the EOF, assign the output and go away.
        if (ch == EOF)
        {
            *line = buf;
            *n    = len;
            *ptr  = 0;

            if (i > 0) return i;
            else return -1;
        }

        // If we hit the length of the buffer, we need to reallocate.
        // The new buffer is extended by twice the size of the current length.
        if (i == len)
        {
            char * new_buf = realloc(buf, len *= 2);

            if (!new_buf) return -1;

            ptr = new_buf + (ptr - buf);
            buf = new_buf;
        }

        // Copy the character to the buffer and break on CR.
        if (ch == '\n') break;

        *ptr++ = ch;
    }

    *ptr = 0;

    // Assign the output.
    *line = buf;
    *n    = len;

    return i;
}
