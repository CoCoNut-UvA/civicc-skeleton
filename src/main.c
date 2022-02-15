#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>

#include "global/globals.h"
#include "palm/str.h"
#include "ccn/ccn.h"

static
void Usage(char *program) {
    char *program_bin = strrchr(program, '/');
    if (program_bin)
        program = program_bin + 1;

    printf("Usage: %s [OPTION...] <civic file>\n", program);
    printf("Options:\n");
    printf("  -h                           This help message.\n");
    printf("  --output/-o <output_file>    Output assembly to output file instead of STDOUT.\n");
    printf("  --verbose/-v                 Enable verbose mode.\n");
    printf("  --breakpoint/-b <breakpoint> Set a breakpoint.\n");
    printf("  --structure/-s               Pretty print the structure of the compiler.\n");
}



/* Parse command lines. Usages the globals struct to store data. */
static int ProcessArgs(int argc, char *argv[])
{
  static struct option long_options[] = {
        {"verbose", no_argument, 0, 'v'},
        {"output",  required_argument, 0, 'o'},
        {"breakpoint", required_argument, 0, 'b'},
        {"structure", no_argument, 0, 's'},
        {0, 0, 0, 0}};

  int option_index;
  int c;

  while (1) {
      c = getopt_long(argc, argv, "hsvo:b:", long_options, &option_index);

      // End of options
      if (c == -1)
          break;

      switch (c) {
      case 'v':
        global.verbose = 1;
        CCNsetVerbosity(PD_V_MEDIUM);
        break;
      case 'b':
        if (optarg != NULL && isdigit(optarg[0])) {
          CCNsetBreakpointWithID((int)strtol(optarg, NULL, 10));
        } else {
            CCNsetBreakpoint(optarg);
        }
        break;
      case 's':
        CCNshowTree();
        break;
      case 'o':
        global.output_file = optarg;
        break;
      case 'h':
        Usage(argv[0]);
        exit(EXIT_SUCCESS);
      case '?':
        Usage(argv[0]);
        exit(EXIT_FAILURE);
      }
  }
   if (optind == argc - 1) {
        global.input_file = argv[optind];
    } else {
        Usage(argv[0]);
        exit(EXIT_FAILURE);
    }
  return 0;
}

// What to do when a breakpoint is reached.
void BreakpointHandler(node_st *root)
{
    TRAVstart(root, TRAV_PRT);
    return;
}

int main (int argc, char **argv)
{
    GLBinitializeGlobals();
    ProcessArgs(argc, argv);

    CCNrun(NULL);
    return 0;
}
