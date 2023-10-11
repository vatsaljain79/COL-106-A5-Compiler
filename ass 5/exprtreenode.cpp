/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

// Write your code below this line

ExprTreeNode::ExprTreeNode()
{
    num = 0;
    id = "vague";
    type = "vague";
    // evaluated_value=NULL;
    left = NULL;
    right = NULL;
}

ExprTreeNode::ExprTreeNode(string t, int v)
{
    id = "vague";
    type = t;
    left = NULL;
    right = NULL;
    // UnlimitedInt *one=new UnlimitedInt (1);
    // val=new UnlimitedRational(v,one);//converted to rational
    // evaluated_value=NULL;
    if (t == "VAL")
    {
        // evaluated_value=val;
        num = v;
    }
}

ExprTreeNode::~ExprTreeNode()
{
    if (right != NULL)
    {
        delete right;
        right = NULL;
    }
    if (left != NULL)
    {
        delete left;
        left = NULL;
    }
}
