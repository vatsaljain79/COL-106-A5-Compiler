/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
// #include <iostream>
// using namespace std;
// Write your code below this line

SymNode::SymNode()
{
    key = "";
    height = 0;
    left = NULL;
    right = NULL;
    par = NULL;
    address=-1;
}

SymNode::SymNode(string k)
{
    key = k;
    height = 0;
    left = NULL;
    right = NULL;
    par = NULL;
    address=-1;
}

SymNode *SymNode::LeftLeftRotation()
{
    SymNode *b = new SymNode(this->key);
    SymNode *a = new SymNode(this->left->key);
    b->address=this->address;
    a->address=this->left->address;
    b->right = this->right;
    b->left = this->left->right;
    b->par = a;
    a->right = b;
    a->left = this->left->left;
    // cout<<"vh";
    if (this->par != NULL)
    {
        if (this->par->left == this)
        {
            par->left = a;
        }
        else
        {
            par->right = a;
        }
    }

    // height balancing
    if (b->left == NULL)
    {
        if (b->right == NULL)
        {
            b->height = 0;
        }
        else
        {
            b->height = b->right->height + 1;
        }
    }
    else
    {
        if (b->right == NULL)
        {
            b->height = b->left->height + 1;
        }
        else
        {
            b->height = max(b->right->height, b->left->height) + 1;
        }
    }
    if (a->left == NULL)
    {
        if (a->right == NULL)
        {
            a->height = 0;
        }
        else
        {
            a->height = a->right->height + 1;
        }
    }
    else
    {
        if (a->right == NULL)
        {
            a->height = a->left->height + 1;
        }
        else
        {
            a->height = max(a->right->height, a->left->height) + 1;
        }
    }

    SymNode *pa = a->par;
    while (pa != NULL)
    {
        if (pa->left == NULL)
        {
            if (pa->right == NULL)
            {
                pa->height = 0;
            }
            else
            {
                pa->height = pa->right->height + 1;
            }
        }
        else
        {
            if (pa->right == NULL)
            {
                pa->height = pa->left->height + 1;
            }
            else
            {
                pa->height = max(pa->right->height, pa->left->height) + 1;
            }
        }
        pa = pa->par;
    }
    return a;
}

SymNode *SymNode::RightRightRotation()
{
    SymNode *b = new SymNode(this->key);
    SymNode *a = new SymNode(this->right->key);
    b->address=this->address;
    a->address=this->right->address;
    b->left = this->left;
    b->right = this->right->left;
    b->par = a;
    a->left = b;
    a->right = this->right->right;
    if (this->par != NULL)
    {
        if (this->par->right == this)
        {
            par->right = a;
        }
        else
        {
            par->left = a;
        }
    }
    // cout<<"till here";
    // height balance
    if (b->left == NULL)
    {
        if (b->right == NULL)
        {
            b->height = 0;
        }
        else
        {
            b->height = b->right->height + 1;
        }
    }
    else
    {
        if (b->right == NULL)
        {
            b->height = b->left->height + 1;
        }
        else
        {
            b->height = max(b->right->height, b->left->height) + 1;
        }
    }
    if (a->left == NULL)
    {
        if (a->right == NULL)
        {
            a->height = 0;
        }
        else
        {
            a->height = a->right->height + 1;
        }
    }
    else
    {
        if (a->right == NULL)
        {
            a->height = a->left->height + 1;
        }
        else
        {
            a->height = max(a->right->height, a->left->height) + 1;
        }
    }

    SymNode *pa = a->par;
    while (pa != NULL)
    {
        if (pa->left == NULL)
        {
            if (pa->right == NULL)
            {
                pa->height = 0;
            }
            else
            {
                pa->height = pa->right->height + 1;
            }
        }
        else
        {
            if (pa->right == NULL)
            {
                pa->height = pa->left->height + 1;
            }
            else
            {
                pa->height = max(pa->right->height, pa->left->height) + 1;
            }
        }
        pa = pa->par;
    }
    return a;
}

SymNode *SymNode::LeftRightRotation()
{
    SymNode *a = this->left;
    SymNode *b = this->left->right;
    a->right = b->left;
    b->left = a;
    this->left = b;
    b->par = this;

    // height balance
    if (a->left == NULL)
    {
        if (a->right == NULL)
        {
            a->height = 0;
        }
        else
        {
            a->height = a->right->height + 1;
        }
    }
    else
    {
        if (a->right == NULL)
        {
            a->height = a->left->height + 1;
        }
        else
        {
            a->height = max(a->right->height, a->left->height) + 1;
        }
    }

    if (b->left == NULL)
    {
        if (b->right == NULL)
        {
            b->height = 0;
        }
        else
        {
            b->height = b->right->height + 1;
        }
    }
    else
    {
        if (b->right == NULL)
        {
            b->height = b->left->height + 1;
        }
        else
        {
            b->height = max(b->right->height, b->left->height) + 1;
        }
    }
    // cout<<"her";
    return this->LeftLeftRotation();
}

SymNode *SymNode::RightLeftRotation()
{
    SymNode *a = this->right;
    SymNode *b = this->right->left;
    a->left = b->right;
    b->right = a;
    this->right = b;
    b->par = this;
    // height balance
    if (a->left == NULL)
    {
        if (a->right == NULL)
        {
            a->height = 0;
        }
        else
        {
            a->height = a->right->height + 1;
        }
    }
    else
    {
        if (a->right == NULL)
        {
            a->height = a->left->height + 1;
        }
        else
        {
            a->height = max(a->right->height, a->left->height) + 1;
        }
    }

    if (b->left == NULL)
    {
        if (b->right == NULL)
        {
            b->height = 0;
        }
        else
        {
            b->height = b->right->height + 1;
        }
    }
    else
    {
        if (b->right == NULL)
        {
            b->height = b->left->height + 1;
        }
        else
        {
            b->height = max(b->right->height, b->left->height) + 1;
        }
    }
    return this->RightRightRotation();
}

SymNode::~SymNode()
{
    if (left != NULL)
    {
        delete left;
        left = NULL;
    }
    if (right != NULL)
    {
        delete right;
        right = NULL;
    }
}
