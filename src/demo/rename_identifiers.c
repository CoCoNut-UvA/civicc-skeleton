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

/**
 * @fn RIvarlet
 */
node_st *RIvarlet(node_st *node)
{
    char *name = NULL;

    name = VARLET_NAME(node);
    VARLET_NAME(node) = STRcat( "__", name);
    MEMfree(name);

    return node;
}

/**
 * @fn RIvar
 */
node_st *RIvar(node_st *node)
{
    char *name = NULL;

    name = VAR_NAME(node);
    VAR_NAME(node) = STRcat("__", name);
    MEMfree(name);

    return node;
}
