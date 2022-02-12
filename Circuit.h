#pragma once
#include "Node.h"
#include "draw.h"
#include "MyQueue.h"
#include "MinHeap.h"
#include <vector>

struct Circuit{
// private:
    int xsize, ysize, numGroups;
    int gridX, gridY;
    Node NN[10000];
    std::vector< Node* > pinsGroup[1000];

    int currentGroup = 0;
    int routedSegment = 0;
    Queue* queue;
    int algorithm = 0;
    int detail = 1;
    bool drawflag = false;

    // public:
    // The circuit is build determained by the different algorithms
    // Using normal queue for the maze while minimal heap for the a* 
    Circuit(int algo, int detail): algorithm(algo), detail(detail){
        if (algorithm == 1) {
            queue = new MinHeap();
        } else if (algorithm ==0) {
            queue = new MyQueue();
        }
        if(detail ==3) {
            drawflag =true;
        }
    }
    bool readFile(const char* testbench);
    void router();
    void resetPointer();
    void resetDistance();
    void resetConnected();
    void pushBackConnected(Node* targetNode);
    void initGraph();
    void updateGraph();
    int calWireLength();
};