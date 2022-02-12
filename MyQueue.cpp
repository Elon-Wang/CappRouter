#include "Node.h"
#include "MyQueue.h"

Node* MyQueue::dequeue(int xBound, int yBound, int groupIdx, bool flag) {
    Node* current = nodeList[head];
    // if newNode is the pin of the same group
    // task complete and trace back;

    if(available( current, current-1, xBound, yBound, groupIdx)){
        (current-1)->previous = current;
        enqueue((current-1), current, flag);
    }
    if(available( current, current+1, xBound, yBound, groupIdx)){
        (current+1)->previous = current;
        enqueue((current+1), current, flag);
    }
    if(available( current, current - xBound, xBound, yBound, groupIdx)){
        (current - xBound)->previous = current;
        enqueue((current-xBound), current, flag);
    }
    if(available( current, current + xBound, xBound, yBound, groupIdx)){
        (current + xBound)->previous = current;
        enqueue((current+ xBound), current, flag);
    }
    
    head++;
    return current;

    // if the newNode belongs to other groups or obstacle, step over

    // if the newNode do not belong to any group, and has a higher distance 
    // from the source, add these nodes to the queue, 
}

void MyQueue::enqueue(Node* newNode, Node* previousNode, bool flag) {
    // just perform the add node bahavior.
    // printf("enque:(%d,%d)\n",newNode->x,newNode->y);
    newNode->distance = (previousNode == NULL)? 0: previousNode->distance+1;
    newNode->value = newNode->distance;
    if (flag == true)
        newNode->updateBlock();
    nodeList[rear] = newNode;    
    rear++;
}

void MyQueue::resetQueue(){
    head=0;
    rear=0;
}

bool MyQueue::available(Node* N1, Node* N2, int xBound, int yBound, int groupIdx){
    //boundary check
    if (N2->x>=0 && N2->y>=0 && N2->x < xBound && N2->y < yBound && (std::abs(N1->x - N2->x) + std::abs(N1->y - N2->y)) ==1 ) {
        // group check
        if (N2->group == 0 || N2->group ==groupIdx) {
            // distance check, avoid an node been added to the queue repeatly.
            if (N2->distance > N1->distance+1) {
                return true;
            }
        }
    }
    return false;
}