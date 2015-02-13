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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
#include "lol.h"
#include "options.h"

int main(int argc, char ** argv)
{
    // Get options.
    options opts;

    int optind = get_opts(argc, argv, &opts);
    if (optind <= 0) return (optind == 0 ? EXIT_SUCCESS : EXIT_FAILURE);

    // It does not make sense if the standard output is not a terminal.
    if (!isatty(fileno(stdout)))
    {
        fprintf(stderr, "Output is not a terminal.\n");
        return EXIT_FAILURE;
    }

    // We need a 256-color terminal.
    setupterm(NULL, fileno(stdout), NULL);
    int ncolors = tigetnum("colors");

    if (ncolors != 256)
    {
        fprintf(stderr, "Terminal supports only %d colors.\n", ncolors);
        return EXIT_FAILURE;
    }

    line_list * list = NULL;
    line_list_create(&list);

    // Take files from arguments.
    if (optind < argc)
    {
        for ( ; optind < argc; optind++)
        {
            FILE * f = strcmp(argv[optind], "-") == 0 ? stdin : fopen(argv[optind], "r");

            if (!f)
            {
                perror(argv[optind]);
                exit(EXIT_FAILURE);
            }

            line_list_add_file(list, f);
            fclose(f);
        }
    }
    // Standard input only.
    else
    {
        line_list_add_file(list, stdin);
    }

    lol(list, opts);

    line_list_destroy(&list);

    return EXIT_SUCCESS;
}

