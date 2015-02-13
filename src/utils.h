#ifndef UTILS_H_
#define UTILS_H_

#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>

// Get line from the stream.
//
// The functions gets a line from the given stream.
//
// If *line is NULL, a new buffer is allocated. Otherwise, the current buffer
// is used. The already allocated buffer can be reallocated if there is not
// enough space for the whole line.
//
// The length of the current buffer is passed through the parameter n.
// On return, n can be changed if the buffer was reallocated.
//
// The function returns the number of characters read. If an error or EOF
// is reached, it returns -1.
//
// The line does not contain the CR character!
//
ssize_t get_line(char ** line, size_t * n, FILE * stream);

#endif /* UTILS_H_ */
