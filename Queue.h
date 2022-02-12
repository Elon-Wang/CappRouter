#pragma once
#include "Node.h"

struct Queue{
    Node* nodeList[100005];
    Node* targetNode;
    virtual void enqueue(Node* newNode, Node* targetNode, bool flag){}
    virtual Node* dequeue(int xBound, int yBound, int groupIdx, bool flag) {
        return new Node();
    }
    virtual int getSize() { return 0;}
    virtual void resetQueue() {}
    virtual bool available(Node* N1, Node* N2, int xBound, int yBound, int groupIdx) {return false;}
};