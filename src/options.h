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
