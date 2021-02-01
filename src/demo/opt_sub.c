/**
 * @file
 *
 * This file contains the code for the OptSubstraction traversal.
 * The traversal has the uid: OS
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"
#include "ccngen/enum.h"
#include "palm/str.h"

/**
 * @fn OSbinop
 */
node_st *OSbinop(node_st *node)
{
    TRAVleft(node);
    TRAVright(node);

    if (BINOP_TYPE( node) == BO_sub) {
        if ((NODE_TYPE( BINOP_LEFT( node)) == NT_VAR)
        && (NODE_TYPE( BINOP_RIGHT( node)) == NT_VAR)
        && STReq( VAR_NAME( BINOP_LEFT( node)), VAR_NAME( BINOP_RIGHT( node)))) {
            node = CCNfree(node);
            node = ASTnum(0);
        } else if  ((NODE_TYPE( BINOP_LEFT( node)) == NT_NUM)
        && (NODE_TYPE( BINOP_RIGHT( node)) == NT_NUM)
        && (NUM_VAL( BINOP_LEFT( node)) == NUM_VAL(BINOP_RIGHT(node)))) {
            node = CCNfree(node);
            node = ASTnum(0);
        }
   }


    return node;
}

