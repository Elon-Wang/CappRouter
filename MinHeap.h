#pragma once
#include "Queue.h"
#include "Node.h"

struct MinHeap : public Queue{
    // Node* nodeList[100005];
    // Node* targetNode;
    Node* emptyNode;
    int size=0;//Note that the nodes[1] is the root of the whole tree;
    void up(int a);
    void down(int a=0);
    void swap(int a,int b);
    void enqueue(Node* newNode, Node* targetNode, bool flag);
    Node* dequeue(int xBound, int yBound, int groupIdx,bool flag);
    void resetQueue();
    bool available(Node* N1, Node* N2, int xBound, int yBound, int groupIdx);
    int getSize(){ 
        // printf("size of the queue:%d\n",size);
        return size; 
    }
    int calDistance(Node* current, Node* destination);
    bool compare(Node* a, Node* b);
    MinHeap(){
        Node tmp = Node(10000,1,1);
        emptyNode = &tmp; 
        nodeList[0] = emptyNode;
    };
};