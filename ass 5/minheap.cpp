/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
// #include "heapnode.cpp"
// #include <iostream>
// #include <vector>

// Write your code below this line

MinHeap::MinHeap()
{
    size = 0;
    root = NULL;
}

void heapifyUp(HeapNode *node)
{
    while (node->par != NULL && node->val < node->par->val)
    {
        swap(node->val, node->par->val);
        node = node->par;
    }
    return;
}

void heapifyDown(HeapNode *NNode)
{
    bool flag = true;
    while (flag)
    {
        HeapNode *leastvalue = NNode;
        if (NNode->left != NULL and NNode->left->val < leastvalue->val)
        {
            leastvalue = NNode->left;
        }
        if (NNode->right != NULL and NNode->right->val < leastvalue->val)
        {
            leastvalue = NNode->right; // taking the min of both right and left valuess
        }

        if (leastvalue == NNode)
        {
            break;
        }

        swap(NNode->val, leastvalue->val);
        NNode = leastvalue;
    }
    return;
}

HeapNode *endingnode(HeapNode *root, int size)
{
    // cout<<"s: "<<size<<endl;
    HeapNode *currentNode = root;
    // cout<<"val: "<<root->right->val<<endl;
    int arr[30];
    int p = size;
    arr[0] = p;
    int arsize = 1;
    while (p > 1)
    {
        // cout<<"hi";
        p = p / 2;
        arr[arsize] = p;
        arsize += 1;
    }
    // cout<<"hsfhi";
    int arrsz = arsize;
    // cout<<arrsz<<endl;
    int j = arrsz - 1;
    while (j > 0)
    {
        // cout << arr[j - 1] << " ";
        if (arr[j] * 2 == arr[j - 1])
        {

            currentNode = currentNode->left;
        }
        else
        {
            currentNode = currentNode->right;
        }
        j -= 1;
    }
    // cout<<"hi: "<< currentNode->val;
    // cout<<"ji";
    return currentNode;
}

HeapNode *parentnode(int idx, HeapNode *root)
{
    // cout<<"ye";
    HeapNode *currentNode = root;
    int arr[30];
    int p = idx;
    arr[0] = p;
    int arsize = 1;
    while (p > 1)
    {
        // cout<<"hi";
        p = p / 2;
        arr[arsize] = p;
        arsize += 1;
    }
    // cout<<"hsfhi";
    int arrsz = arsize;
    // cout<<arrsz<<endl;
    int j = arrsz - 1;
    while (j > 1)
    {
        // cout << arr[j - 1] << " ";
        if (arr[j] * 2 == arr[j - 1])
        {
            currentNode = currentNode->left;
        }
        else
        {
            currentNode = currentNode->right;
        }
        j -= 1;
    }
    // cout << "val:" << currentNode->val << endl;
    return currentNode;
}

void MinHeap::push_heap(int num)
{
    HeapNode *pushnode = new HeapNode(num);
    if (size == 0)
    {
        root = pushnode;
    }
    else
    {
        HeapNode *nodepar = parentnode(size + 1, root);
        // cout<<"par val: "<<parent->val<<endl;
        if (nodepar->left == NULL)
        {
            nodepar->left = pushnode;
        }
        else
        {
            nodepar->right = pushnode;
        }
        pushnode->par = nodepar;
        heapifyUp(pushnode);
        // cout<<"par val: "<<parent->val<<endl;
    }
    size++;
    return;
}

int MinHeap::get_min()
{
    if (size != 0)
    {
        return root->val;
    }
    else
    {
        return 0;
    }
}

void MinHeap::pop()
{
    // cout<<"ye";
    if (size > 0)
    {
        HeapNode *lastNode = endingnode(root, size);
        // cout << lastNode->val << endl;
        swap(root->val, lastNode->val);
        if (lastNode->par)
        {
            if (lastNode->par->left == lastNode)
            {
                lastNode->par->left = NULL;
            }
            else
            {
                lastNode->par->right = NULL;
            }
        }
        size--;
        // cout<<"ye";
        // delete lastNode;
        heapifyDown(root);
    }

    return;
}

MinHeap::~MinHeap()
{
    // if (root!=nullptr){
    //     delete root;
    //     root=nullptr;
    // }
}

// int main()
// {

//     MinHeap h;
//     //     h.push_heap(12);
//     //     cout<<h.get_min()<<endl;
//     //     h.push_heap(13);
//     //     cout<<h.get_min()<<endl;
//     //     h.push_heap(1);
//     //     cout<<h.get_min()<<endl;
//     //     h.push_heap(-87);
//     //     cout<<h.get_min()<<endl;
//     //     // cout<<9;
//     //     h.pop();
//     //     cout<<h.get_min()<<endl;
//     //     h.pop();

//     //     // h.push_heap(1);
//     //     // h.push_heap(11);
//     //     // h.push_heap(10);
//     // h.push_heap(1);

//     // // h.push_heap(2);
//     // h.pop();

//     int j = 10;
//     while (j > 0)
//     {

//         h.pop();
//         h.push_heap(j);
//         cout << h.get_min() << endl;

//         j--;
//     }
//     //     cout<<h.get_min()<<endl;
// }