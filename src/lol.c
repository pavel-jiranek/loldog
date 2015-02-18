#include "lol.h"

#include <stddef.h>
#include <stdio.h>
#include <term.h>

#include "config.h"
#if defined(CURSES_HAVE_CURSES_H)
#include <curses.h>
#elif defined(CURSES_HAVE_NCURSES_H)
#include <ncurses.h>
#elif defined(CURSES_HAVE_NCURSES_NCURSES_H)
#include <ncurses/ncurses.h>
#elif defined(CURSES_HAVE_NCURSES_CURSES_H)
#include <ncurses/curses.h>
#else
#error No CURSES header!
#endif

#include "linelist.h"
#include "options.h"

// Color schemes.

int colors_rainbow[] =
{
    196, 202, 208, 214, 220, 226, 190, 154, 118,  82,
    46,  47,  48,  49,  50,  51,  45,  39,  33,  27,
    21,  57,  93, 129, 165, 201
};

size_t const num_colors_rainbow = 26;

int colors_gray[] =
{
    236, 237, 238, 239, 240, 241, 242, 243, 244, 245,
    246, 247, 248, 249, 250, 251, 252, 253, 254, 255
};
// ... We skip the first 4 colors from the "full" gray scale to make
//     the dark colors at least somewhat visible.

size_t const num_colors_gray = 20;

int colors_jet[] =
{
    196, 202, 208, 214, 220, 226, 190, 154, 118,  82,
    46,  47,  48,  49,  50,  51,  45,  39,  33,  27,
    21
};

size_t const num_colors_jet = 21;

int colors_hot[] =
{
    231, 230, 229, 228, 227, 226, 220, 214, 208, 202,
    196, 196, 160, 124
};

size_t const num_colors_hot = 14;

int colors_cool[] =
{
    201, 165, 129,  93,  57,  21,  27,  33,  39,  45,
    51
};

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
        return i % size;
}

size_t get_num_colors(size_t size, int bounce)
{
    return (bounce ? 2 * size - 2 : size);
}

// Row-wise scaled LOL.
int lol_rws(line_list * list, int const * colors, size_t num_colors, int bounce)
{
    char * setaf = tigetstr("setaf");
    char * op    = tigetstr("op");

    size_t num_all_colors = get_num_colors(num_colors, bounce);
    int i_row = 0;
    line_list_node * node = list->first;

    for (; node != NULL ; node = node->next, i_row++)
    {
        int row_iter = (i_row * num_all_colors) / list->size;
        int i_color = get_color_index(row_iter, num_colors, bounce);
        putp(tparm(setaf, colors[i_color]));
        fprintf(stdout, "%s\n", node->line);
        putp(op);
    }

    return 1;
}

// Row-wise LOL.
int lol_rw(line_list * list, int const * colors, size_t num_colors, int rinc, int bounce)
{
    char * setaf = tigetstr("setaf");
    char * op    = tigetstr("op");

    int i_row = 0, row_iter = 0;
    line_list_node * node = list->first;

    for (; node != NULL ; node = node->next, i_row++)
    {
        int i_color = get_color_index(row_iter, num_colors, bounce);
        putp(tparm(setaf, colors[i_color]));
        fprintf(stdout, "%s\n", node->line);
        putp(op);

        if (rinc && (i_row % rinc == rinc - 1)) row_iter++;
    }

    return 1;
}

// Diagonal LOL.
int lol_dg(line_list * list, int const * colors, size_t num_colors, int rinc, int cinc, int bounce)
{
    char * setaf = tigetstr("setaf");
    char * op    = tigetstr("op");

    int i_row = 0, row_iter = 0;
    line_list_node * node = list->first;

    for (; node != NULL ; node = node->next, i_row++)
    {
        int col_shift = 0;
        char * ch = node->line;

        for (; *ch; ch++, col_shift++)
        {
            if ((cinc && col_shift % cinc == 0) || !cinc)
            {
                int col_iter = row_iter + (cinc ? col_shift / cinc : 0);
                int i_color = get_color_index(col_iter, num_colors, bounce);
                putp(tparm(setaf, colors[i_color]));
            }

            fputc(*ch, stdout);
        }

        fprintf(stdout, "\n");
        putp(op);

        if (rinc && (i_row % rinc == rinc - 1)) row_iter++;
    }

    return 1;
}

// Main LOL-stuff.
int lol(line_list * list, options opts)
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
            ret = lol_rw(list, colors, num_colors, opts.rinc, opts.bounce);
            break;

        case LT_RWS:
            ret = lol_rws(list, colors, num_colors, opts.bounce);
            break;

        case LT_DG:
            ret = lol_dg(list, colors, num_colors, opts.rinc, opts.cinc, opts.bounce);
            break;
    }

    return ret;
}
