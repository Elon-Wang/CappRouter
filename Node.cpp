#include "Node.h"
#include "draw.h"

void Node::traceBack(int groupIdx){
    // printf("traceback(%d,%d)\n",this->x, this->y);
    // if previous equal to Null, exit the recursion
    // if not equal to Null, continue traceback.
    if (this->previous == NULL){
        return;
    } else {
        this->distance = 0;
        this->cost =0;
        // change the groups of this node
        this->group = groupIdx;
        //traceBack to the previous node.
        this->previous->traceBack(groupIdx);
        this->connected = true;
    }   
}

void Node::updateBlock(){
    if (connected ==false) {
        setcolor(3);
        fillrect(2 + x * 10, 2 + y * 10, 2 + (x + 1) * 10, 2 + (y + 1) * 10);
        setfontsize(20);
        setcolor(1);
        char pinIdx[10];
        sprintf(pinIdx, "val:%d", value);
        drawtext(7 + x * 10, 9 + y * 10, pinIdx, 10);
    } 
}