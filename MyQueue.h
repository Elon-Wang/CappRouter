#pragma once
#include "Queue.h"
#include "Node.h"

struct MyQueue : public Queue{
    // Node* nodeList[100005];
    int head = 0;
    int rear = 0;
    void enqueue(Node* newNode, Node* previous, bool flag);
    Node* dequeue(int xBound, int yBound, int groupIdx, bool flag);
    int getSize()  {return (rear - head);}
    void resetQueue();
    bool available(Node* N1, Node* N2, int xBound, int yBound, int groupIdx);
};