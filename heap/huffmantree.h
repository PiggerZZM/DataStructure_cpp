#include "minheap.h"
const int DefaultSize = 20;
struct HuffmanNode
{
    float data;
    HuffmanNode *leftChild, *rightChild, *parent;
    HuffmanNode():leftChild(NULL),rightChild(NULL),parent(NULL){}
    HuffmanNode(float elem, HuffmanNode* left = NULL, HuffmanNode* right = NULL, HuffmanNode* pr = NULL):data(elem),leftChild(left),rightChild(right),parent(pr){}
    bool operator <= (HuffmanNode& R) {return data <= R.data;}
    bool operator > (HuffmanNode& R) {return data > R.data;}
};

class HuffmanTree
{
private:
    HuffmanNode *root;
    void deleteTree(HuffmanNode *t);
    void mergeTree(HuffmanNode& ht1, HuffmanNode&ht2, HuffmanNode*& parent);
public:
    HuffmanTree(float w[], int n);
    ~HuffmanTree(){delete []root;}
}

HuffmanTree::HuffmanTree(float w[], int n)
{
    MinHeap hp;
    HuffmanNode *parent,first,second,work;
    for(int i=0;i<n;i++)
    {
        work.data = w[i];
        work.leftChild = NULL;
        work.rightChild = NULL;
        work.parent = NULL;
        hp.Insert(work);
    }
    for(int i=0;i<n-1;i++)
    {
        hp.RemoveMin(first);
        hp.RemoveMin(second);
        merge(first,second,parent);
        hp.Insert(*parent);
    }
    root = parent;
}

void HuffmanTree::mergeTree(HuffmanNode &bt1, HuffmanNode &bt2, HuffmanNode *&parent)
{
    parent = new HuffmanNode;
    parent->leftChild = &bt1;
    parent->rightChild = &bt2;
    parent->data = bt1.root->data + bt2.root->data;
    bt1.root->parent = bt2.root->parent = parent;
}