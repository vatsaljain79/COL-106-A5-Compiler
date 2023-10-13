/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode(){
    par=NULL;
    left=NULL;
    right=NULL;
    val=0;
}

HeapNode::HeapNode(int _val){
    par=NULL;
    left=NULL;
    right=NULL;
    val=_val;
}

HeapNode::~HeapNode(){
    if (par!=NULL){
        delete par;
        par=NULL;
    }
    if (left!=NULL){
        delete left;
        left=NULL;
    }
    if (right!=NULL){
        delete right;
        right=NULL;
    }
  
}