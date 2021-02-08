#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <argp.h>

#include "global/globals.h"
#include "palm/str.h"
#include "ccn/ccn.h"

// Uses argp: https://www.gnu.org/software/libc/manual/html_node/Argp.html

/* Program documentation. */
static char doc[] =
  "civicc -- Programming C, the civilised way.";

/* A description of the arguments we accept. */
static char args_doc[] = "<civic file>";


static struct argp_option options[] = {
  {"verbose",    'v', "INT",      0,  "Produce verbose output", 0},
  {"output",     'o', "FILE", 0,  "Output to file instead of STDOUT", 0},
  {"breakpoint", 'b', "BREAK", 0, "Break at the action in your compiler given by the breakstring(<phase>.<action>) or the id seen in the structure", 0},
  {"structure", 's', NULL, 0, "Show the structure of the compiler.", 0},
  { 0 }
};

/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct globals *globals = state->input;

    switch (key)
    {
    case 'v':
      globals->verbose = (int)strtol(arg, NULL, 10);
      CCNsetVerbosity(globals->verbose);
      break;
    case 'o':
      globals->output_file = arg;
      break;

    case 'b':
      if (arg != NULL && isdigit(arg[0])) {
          CCNsetBreakpointWithID((int)strtol(arg, NULL, 10));
      } else {
          CCNsetBreakpoint(arg);
      }
      break;
    case 's':
      CCNshowTree();
      break;
    case ARGP_KEY_ARG:
        if (state->arg_num >= 2) {
            /* Too many arguments. */
            argp_usage (state);
        }
        globals->input_file = arg; 
        break;

    case ARGP_KEY_END:
      if (state->arg_num < 1)
        /* Not enough arguments. */
        argp_usage (state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0};

// What to do when a breakpoint is reached.
void BreakpointHandler(node_st *root)
{
    TRAVstart(root, TRAV_PRT);
    return;
}

int main (int argc, char **argv)
{
    GLBinitializeGlobals();
    argp_parse (&argp, argc, argv, 0, 0, &global);

    CCNrun(NULL);
    return 0;
}
