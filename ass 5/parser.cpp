/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    symtable = new SymbolTable();
}

Parser::~Parser(){
    delete symtable;
    int n=expr_trees.size();
    while (n){
        ExprTreeNode * node=expr_trees[n-1];
        while (node!=NULL){
            if (node->left!=NULL){
                delete node->left;
                node->left=NULL;
            }
            if (node->right!=NULL){
                delete node->right;
                node->right=NULL;
            }
            delete node;
            node=NULL;
        }
        n-=1;
    }
}

string signcheck(char c)
{

    if (int(c) == 37)
    {
        return "MOD";
    }
    else if (int(c) == 42)
    {
        return "MUL";
    }
    else if (int(c) == 43)
    {
        return "ADD";
    }
    else if (int(c) == 45)
    {
        return "SUB";
    }
    else if (int(c) == 47)
    {

        return "DIV";
    }
    else
    {
        return "VAR";
    }
}

ExprTreeNode *recurparse(vector<string> expression, int startindex, int endindex)
{
    if (startindex < endindex)
    {
        if ((47 < int(expression[startindex + 1][0]) and int(expression[startindex + 1][0]) < 58) or (expression[startindex+1][0]=='-' and expression[startindex+1].size()>1 and (47 < int(expression[startindex + 1][1]) and int(expression[startindex + 1][1]) < 58) )) // means its a number ahead;
        {
            // cout<<"f"<<expression[startindex+1];
            int num = stoi(expression[startindex + 1]);
            string numtype = "VAL";
            ExprTreeNode *numnode = new ExprTreeNode(numtype, num);
            ExprTreeNode *signnode = new ExprTreeNode;
            numnode->id = expression[startindex + 1];
            signnode->type = signcheck(expression[startindex + 2][0]);
            signnode->left = numnode;
            signnode->id = expression[startindex + 2];
            // cout<<signnode->id<<endl;
            // cout<<"start "<<startindex<<"end "<<endindex<<endl;
            signnode->right = recurparse(expression, startindex + 3, endindex - 1);
            // cout<<"enter"<<endl;
            return signnode;
        }
        else 
        // if (expression[startindex+1]=="(")
        { // means its a bracket ahead;
            int countbracket = 0;
            int indexcheck = 0;
            for (int j = startindex + 1; j < endindex; j++)
            {
                if (int(expression[j][0]) == 40)
                {
                    countbracket += 1;
                }
                else if (int(expression[j][0]) == 41)
                {
                    countbracket -= 1;
                }
                if (countbracket == 0)
                {
                    indexcheck = j;
                    break;
                }
            }
            ExprTreeNode *signnode = new ExprTreeNode;
            signnode->type = signcheck(expression[indexcheck + 1][0]);
            signnode->left = recurparse(expression, startindex + 1, indexcheck);
            signnode->right = recurparse(expression, indexcheck + 2, endindex - 1);
            signnode->id = expression[indexcheck + 1];
            return signnode;
        }
    }
    else if (startindex > endindex)
    {
        return NULL;
    }
    else
    {

        // cout<<"jho";
        // cout<<5;
        // cout<<startindex+1;
        // int a=int(expression[startindex + 1][0]);
        // cout<<a;
        if ((47 < int(expression[startindex ][0]) and int(expression[startindex][0]) < 58) or (expression[startindex][0]=='-' and expression[startindex].size()>1 and (47 < int(expression[startindex ][1]) and int(expression[startindex ][1]) < 58) )) // means its a number ahead;
        {
            // cout<<"ko";
            int num = stoi(expression[startindex]);
            string numtype = "VAL";
            ExprTreeNode *numnode = new ExprTreeNode(numtype, num);
            numnode->id = expression[startindex];
            return numnode;
        }
        else
        {
            // cout<<"here"<<endl;
            ExprTreeNode *variable = new ExprTreeNode();
            variable->type = "VAR";
            variable->id = expression[startindex];
            // cout<<variable->id;
            return variable;
        }
    }
}

void Parser::parse(vector<string> expression)
{
    ExprTreeNode *main = new ExprTreeNode();
    main->type = "equalto";
    main->id = expression[1];

    ExprTreeNode *leftmain = new ExprTreeNode();
    main->left = leftmain;
    leftmain->type = "VAR";
    leftmain->id = expression[0];

    if (leftmain->id=="del"){
        leftmain->type="DEL";
    }
    if (leftmain->id=="ret"){
        leftmain->type="RET";
    }
    
    
    int startindex = 2;
    int size = expression.size();
    int endindex = size - 1;

    if (expression[2] != "(")
    {
        // cout<<"hi";

        if ((47 < int(expression[2][0]) and int(expression[2][0]) < 58) or (expression[2][0]=='-' and expression[2].size()>1 and (47 < int(expression[2 ][1]) and int(expression[2 ][1]) < 58) )) // means its a number ahead;
        {
            // cout<<"ko";
            int num = stoi(expression[2]);
            string numtype = "VAL";
            ExprTreeNode *numnode = new ExprTreeNode(numtype, num);
            numnode->id = expression[2];
            main->right = numnode;
            // return numnode;
        }
        else
        {
            // cout<<"here";
            ExprTreeNode *variable = new ExprTreeNode();
            variable->type = "VAR";
            variable->id = expression[2];
            main->right = variable;
            // return variable;
        }
        expr_trees.push_back(main);
    }
    else
    {
        main->right = recurparse(expression, startindex, endindex);
        expr_trees.push_back(main);
    }
}


