/**
 * @file
 *
 * This file contains the code for the SumInstructions traversal.
 * The traversal has the uid: SI
 */

#include <stdio.h>

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav_data.h"

void SIinit() { return; }
void SIfini() { return; }

/**
 * @fn SIprogram
 */
node_st *SIprogram(node_st *node)
{
    TRAVchildren(node);

    struct data_si *data = DATA_SI_GET();
    printf("Sum of integers: %d\n", data->sum);

    return node;
}


/**
 * @fn SInum
 */
node_st *SInum(node_st *node)
{
    struct data_si *data = DATA_SI_GET();
    data->sum += NUM_VAL(node);
    return node;
}

