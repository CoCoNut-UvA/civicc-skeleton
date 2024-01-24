/**
 * @file
 *
 * This file contains the code for the RenameIdentifiers traversal.
 * The traversal has the uid: RI
 *
 * @brief This module implements a demo traversal of the abstract syntax tree that
 * prefixes any variable found by two underscores.
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "palm/str.h"
#include "palm/memory.h"


static void rename_var(node_st *node)
{
    char *name = NULL;

    name = VARS_NAME(node);
    VARS_NAME(node) = STRfmt("__%s", name);
    MEMfree(name);
}

/**
 * @fn RIvarlet
 */
node_st *RIvarlet(node_st *node)
{
    rename_var(node);
    return node;
}

/**
 * @fn RIvar
 */
node_st *RIvar(node_st *node)
{
    rename_var(node);
    return node;
}
