/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
// #include
// #include <bits/stdc++.h>
// #include <iostream>
// using namespace std;
// Write your code below this line


EPPCompiler::EPPCompiler()
{
    output_file = "";
    memory_size = 0;
    least_mem_loc=MinHeap();
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
    output_file = out_file;
    memory_size = mem_limit;
    int i = 0;
    least_mem_loc=MinHeap();
    while (i <mem_limit)
    {
        least_mem_loc.push_heap(i);
        i++;
    }
}

void EPPCompiler::compile(vector<vector<string>> code)
{
    int sz = code.size();
    // output_file.erase();
    std::fstream Object;
    Object.open(output_file,std::ios::out | std::ios::trunc);
    
    for (int i = 0; i < sz; i++)
    {
        vector<string> v1 = code[i];
        targ.parse(v1);
        vector<string> commandd;
        if (v1[0] != "del" and v1[0]!="ret")
        {
            commandd = generate_targ_commands();
        }
        else if (v1[0]=="ret"){
            commandd = generate_targ_commands();
            commandd.push_back("RET = POP");
            i=sz;
        }
        else
        {
            string var = v1[2];
            commandd = {};
            int address = targ.symtable->search(var);
            targ.symtable->remove(var);
            string sdel = "DEL = mem[" + std::to_string(address) + "]";
            commandd.push_back(sdel);
            least_mem_loc.push_heap(address); // need to insert it in sorted reverse
        }
        write_to_file(commandd);
        commandd = {};
    }
}

void postorder(ExprTreeNode *root, vector<string> &postOrder)
{
    if (root == NULL)
    {
        return;
    }
    postorder(root->right, postOrder);
    postorder(root->left, postOrder);
    postOrder.push_back(root->id);
}

string signncheck(char c)
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
        return "VaAR";
    }
}

vector<string> EPPCompiler::generate_targ_commands()
{
    ExprTreeNode *node = targ.expr_trees.back();
    vector<string> postOrder;
    
    vector<string> command;
    postorder(node->right, postOrder);
    for (int p = 0; p < postOrder.size(); p++)
    {
        string s = postOrder[p];
        if ((int(s[0]) > 47 && int(s[0]) < 58) or (s[0] == '-' and s.size() > 1 and int(s[1]) > 47 && int(s[1]) < 58))
        {
            string k = "PUSH " + s;
            command.push_back(k);
        }
        else if (signncheck(s[0]) != "VaAR")
        {
            command.push_back(signncheck(s[0]));
        }
        else
        {
            int address = targ.symtable->search(s);
            string k = "PUSH mem[" + std::to_string(address) + "]";
            command.push_back(k);
        }
    }
    if (node->left->id != "ret")
    {
        string vari = node->left->id; 
        if (targ.symtable->search(vari) == -2)
        {
            targ.symtable->insert(vari);
            int address = least_mem_loc.get_min();
            targ.symtable->assign_address(vari, address);
            least_mem_loc.pop();
            string mem = "mem[" + std::to_string(address) + "] = POP";
            command.push_back(mem);
        }else{
            // cout<<"here";
            int address=targ.symtable->search(vari);
            string mem = "mem[" + std::to_string(address) + "] = POP";
            command.push_back(mem);
        }
    }
    targ.expr_trees.pop_back();
    return command;
}

void EPPCompiler::write_to_file(vector<string> commands)
{
    ofstream outcfile(output_file, ios::app);
    int i = 0;
    while (i < commands.size())
    {
        outcfile<< commands[i] << std::endl;
        i++;
    }
    outcfile.close();
}

EPPCompiler::~EPPCompiler()
{
    // memory_size=0;
    // least_mem_loc={};
    // targ.~Parser();
}
