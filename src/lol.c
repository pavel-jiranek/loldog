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

#include "lol.h"

#include "linelist.h"
#include "utils.h"

// Color schemes.

int colors_rainbow[] = {
                196, 202, 208, 214, 220, 226, 190, 154, 118,  82,
                46,  47,  48,  49,  50,  51,  45,  39,  33,  27,
                21,  57,  93, 129, 165, 201 };

size_t const num_colors_rainbow = 26;

int colors_gray[] = {
                236, 237, 238, 239, 240, 241, 242, 243, 244, 245,
                246, 247, 248, 249, 250, 251, 252, 253, 254, 255 };
// ... We skip the first 4 colors from the "full" gray scale to make
//     the dark colors at least somewhat visible.

size_t const num_colors_gray = 20;

int colors_jet[] = {
                196, 202, 208, 214, 220, 226, 190, 154, 118,  82,
                 46,  47,  48,  49,  50,  51,  45,  39,  33,  27,
                 21 };

size_t const num_colors_jet = 21;

int colors_hot[] = {
                231, 230, 229, 228, 227, 226, 220, 214, 208, 202,
                196, 196, 160, 124 };

size_t const num_colors_hot = 14;

int colors_cool[] = {
                201, 165, 129,  93,  57,  21,  27,  33,  39,  45,
                51 };

size_t const num_colors_cool = 11;

// Get color index.
//
// The functions gets the index in the color scheme of the given size
// associated with the given "iteration" index. The flag bounce indicates,
// whether the colors are passed as first-to-last or first-to-last-to-first.
int get_color_index(int i, size_t size, int bounce)
{
    if (bounce && size > 1)
    {
        int j = i % (2 * size - 2);
        return (j < size ? j : 2 * size - j - 2);
    }
    else
    {
        return i % size;
    }
}

size_t get_num_colors(size_t size, int bounce)
{
    return (bounce ? 2 * size - 2 : size);
}

// Row-wise scaled LOL.
int lol_rws(FILE * stream, int const * colors, size_t num_colors, int bounce)
{
    // Create the line list.
    line_list * list;
    if (!line_list_create(&list)) return 0;

    for ( ; ; )
    {
        // Get the line from the stream.
        size_t n;
        char * line = NULL;

        if (get_line(&line, &n, stream) < 0) break;

        // Append the line to the list or exit.
        if (!line_list_add(list, line)) return 0;
    }

    int i = 0;
    line_list_node * node = list->first;
    for ( ; node != NULL ; node = node->next, i++)
    {
        int j = (i * get_num_colors(num_colors, bounce)) / list->size;
        int color = get_color_index(j, num_colors, bounce);
        fprintf(stdout, "\e[38;5;%dm%s\e[0m", colors[color], node->line);
    }

    line_list_destroy(&list);

    return 1;
}

// Row-wise LOL.
int lol_rw(FILE * stream, int const * colors, size_t num_colors, int rinc, int bounce)
{
    int i = 0, k = 0;

    size_t n;
    char * line = NULL;

    for ( ; ; i++)
    {
        if (get_line(&line, &n, stream) < 0) break;

        int color = get_color_index(k, num_colors, bounce);
        fprintf(stdout, "\e[38;5;%dm%s\e[0m", colors[color], line);

        if (rinc && i % rinc == rinc - 1) k++;
    }

    return 1;
}

// Diagonal LOL.
int lol_dg(FILE * stream, int const * colors, size_t num_colors, int rinc, int cinc, int bounce)
{
    int i = 0, k = 0;

    size_t n;
    char * line = NULL;

    for ( ; ; i++)
    {
        if (get_line(&line, &n, stream) < 0) break;

        int j = 0;
        char * c = line;

        for ( ; *c; c++, j++)
        {
            if (j % cinc == 0)
            {
                int color = get_color_index(k + j / cinc, num_colors, bounce);
                fprintf(stdout, "\e[38;5;%dm", colors[color]);
            }
            if (*c == '\n') fprintf(stdout, "\e[0m");
            fputc(*c, stdout);
        }

        if (rinc && i % rinc == rinc - 1) ++k;
    }

    fprintf(stdout, "\e[0m");

    return 1;
}

// Main LOL-stuff.
int lol(FILE * stream, options opts)
{
    int * colors = NULL;
    size_t num_colors = 0;

    switch (opts.cs)
    {
        case CS_RAINBOW:
            colors = colors_rainbow;
            num_colors = num_colors_rainbow;
            break;
        case CS_GRAY:
            colors = colors_gray;
            num_colors = num_colors_gray;
            break;
        case CS_JET:
            colors = colors_jet;
            num_colors = num_colors_jet;
            break;
        case CS_HOT:
            colors = colors_hot;
            num_colors = num_colors_hot;
            break;
        case CS_COOL:
            colors = colors_cool;
            num_colors = num_colors_cool;
            break;
    }

    if (!colors) return 0;

    int ret;
    switch (opts.lt)
    {
        case LT_RW:
            ret = lol_rw(stream, colors, num_colors, opts.rinc, opts.bounce);
            break;
        case LT_RWS:
            ret = lol_rws(stream, colors, num_colors, opts.bounce);
            break;
        case LT_DG:
            ret = lol_dg(stream, colors, num_colors, opts.rinc, opts.cinc, opts.bounce);
            break;
    }

    return ret;
}
