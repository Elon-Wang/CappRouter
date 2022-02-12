#include "Node.h"
#include "MinHeap.h"

void MinHeap::enqueue(Node* newNode, Node* targetNode, bool flag){
    // printf("enque(%d,%d)\n",newNode->x,newNode->y);
    size++;
    nodeList[size]= newNode;
    // calculate the manhaton distance.
    newNode->distance = calDistance(targetNode,newNode);
    newNode->value = (newNode->previous == NULL)? newNode->distance : newNode->distance + newNode->cost;
    if (flag == true) {
        newNode->updateBlock();
    }
    up (size);
}

Node* MinHeap::dequeue(int xBound, int yBound, int groupIdx, bool flag){
    Node* current = nodeList[1];
    // printf("enque(%d,%d)\n",current->x,current->y);
    nodeList[1]= nodeList[size];
    nodeList[size]= emptyNode;
    size--;
    down (1);
    //TODO:finish the avilabel test and enqueue
    if(available( current, current-1, xBound, yBound, groupIdx)){
        (current-1)->previous = current;
        (current-1)->cost = current->cost+1;
        enqueue((current-1),targetNode,flag);
    }
    if(available( current, current+1, xBound, yBound, groupIdx)){
        (current+1)->previous = current;
        (current+1)->cost = current->cost+1;
        enqueue((current+1),targetNode,flag);
    }
    if(available( current, current - xBound, xBound, yBound, groupIdx)){
        (current - xBound)->previous = current;
        (current - xBound)->cost = current->cost+1;
        enqueue((current-xBound),targetNode,flag);
    }
    if(available( current, current + xBound, xBound, yBound, groupIdx)){
        (current + xBound)->previous = current;
        (current + xBound)->cost = current->cost+1;
        enqueue((current+ xBound),targetNode,flag);
    }

    return current;
}
 
void MinHeap::swap(int a,int b) {
    // printf("swap for nodeList[%d] and nodeList[%d]\n",a ,b);
    Node* temp  = nodeList[a];
    nodeList[a] = nodeList[b];
    nodeList[b] = temp;
}
 
void MinHeap::up(int a) {
    // printf("up for Nodelist[%d]\n",a);
    // printf("compare: %d, %d\n",nodeList[a]->distance,nodeList[a/2]->distance);
    if ( compare( nodeList[a], nodeList[a/2]) && a>1) {
        swap (a, a / 2);
        up (a/2);
    }
}
 
void MinHeap::down(int a) {
    int tgt=-1;
    if (2*a < size)
        tgt = ( compare( nodeList[2*a], nodeList[2*a+1]))? 2*a : (2*a + 1);
    else if (2*a == size)
        tgt = size;
    else return;
    if (  compare( nodeList[tgt], nodeList[a]) && tgt >0){
        swap (a,tgt);
        down (tgt);
    }
}

void MinHeap::resetQueue(){
    for(int i=0;i<size;i++){
        nodeList[i] = emptyNode;
    }
    size =0;
}

bool MinHeap::available(Node* N1, Node* N2, int xBound, int yBound, int groupIdx){
    // printf("pos(%d,%d)\n",N2->x,N2->y);
    //boundary check
    if (N2->x>=0 && N2->y>=0 && N2->x < xBound && N2->y < yBound && calDistance(N1,N2) ==1 ) {
        // group check
        if (N2->group == 0 || N2->group ==groupIdx) {
            // avoid an node been added to the queue repeatly.
            if (N2->distance > calDistance(N2,targetNode) || N2->cost > N1->cost+1) {
                return true;
            }
        }
    }
    return false;
}

int MinHeap::calDistance(Node* current, Node* destination){
    return (std::abs(destination->x - current->x) + std::abs(destination->y - current->y));
}

bool MinHeap::compare(Node* a, Node* b){
    if (a->value < b->value){
        return true;
    } else {
        return false;
    }
}