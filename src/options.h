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

#ifndef OPTIONS_H_
#define OPTIONS_H_

// LOL-type.
enum LT
{
    LT_RW,  // Row-wise.
    LT_RWS, // Row-wise scaled.
    LT_DG   // Diagonal.
};

// Color scheme.
enum CS
{
    CS_RAINBOW,
    CS_GRAY,
    CS_JET,
    CS_HOT,
    CS_COOL
};

// Options.
struct options_struct
{
        enum LT lt;     // LOL-type.
        enum CS cs;     // Color scheme.
        int     rinc;   // Row color increment.
        int     cinc;   // Column color increment.
        int     bounce; // Bounce when hit the end of the color scheme.
};

typedef struct options_struct options;

// Get options from the arguments.
//
// The function returns:
//
// * number of unparsed options on success; 0 indicates that no files are
//   going to be processed.
// * -1 on failure;
//
int get_opts(int argc, char ** argv, options * opts);

#endif /* OPTIONS_H_ */
