#include "Node.h"
#include "draw.h"
#include "Circuit.h"
#include "MinHeap.h"
#include <vector>
#include "MyQueue.h"

bool Circuit::readFile(const char* testbench){
    if(!freopen(testbench,"r",stdin)) {
        freopen("/dev/tty","r",stdin);
        // printf("Error opening file\n"); 
        return false;
    }
    printf("open file:%s\n",testbench);
    scanf("%d %d",&xsize,&ysize);

    // set up nodes inside the grid
    for (int cnt =0; cnt< xsize*ysize; cnt++){
        NN[cnt] = Node(cnt, xsize, ysize);
    }

    // set up Obstacle
    int numObstacle;
    scanf("%d",&numObstacle);
    for(int cnt=0; cnt<numObstacle; cnt++) {
        scanf("%d %d",&gridX,&gridY);
        NN[gridX + gridY*xsize].group = -1;
    }
    
    // set up pins
    int pinsInsideGroup;
    scanf("%d",&numGroups);
    for(int cnt=0; cnt< numGroups; cnt++) {
        scanf("%d",&pinsInsideGroup);
        for (int i = 0; i < pinsInsideGroup; i++) {
            scanf("%d %d", &gridX, &gridY);
            NN[gridX + gridY*xsize].group = cnt + 1;
            NN[gridX + gridY*xsize].isPin = true;
            pinsGroup[cnt].push_back(&NN[gridX + gridY*xsize]);
        }    
    }
    freopen("/dev/tty","r",stdin);
    return true;
}

void Circuit::router(){
    while (currentGroup < numGroups) {   
        // makes the source of this group of pins connected.
        // If the number of the achieved nodes less than the required nodes,
        // add the the connected nodes to the queue and find the next pin.
        pinsGroup[currentGroup][0]->connected = true;
        int numOfConnected = 1; 

        if (detail >=2 ) {
            updateGraph();
            printf("\n\n Pins Group %d/%d\n", currentGroup+1,numGroups);
        }
            
        
        while (numOfConnected < pinsGroup[currentGroup].size() ) {
            Node* nextForAstar = NULL;
            if( algorithm == 1){
                nextForAstar = pinsGroup[currentGroup][numOfConnected];
                queue->targetNode = pinsGroup[currentGroup][numOfConnected];
            }
            queue->resetQueue();
            pushBackConnected(nextForAstar);
            resetPointer();
            resetDistance();

            // for maze using the Queue
                // update the distance to the connected nodes.
                // enque/deque
            // for astar uisng the priority queue (Heap)
                // calculate the manhaton dis as the value of the node 
                // enque/deque
            
            while( queue->getSize()>0) {
                Node* tmp = queue->dequeue(xsize,ysize, pinsGroup[currentGroup][0]->group, drawflag);
                if (detail == 3) {
                    event_loop(button_press,drawscreen);
                }
                    
                // if find the pin that is not connected
                // trackback to find the path to the source.
                // reset the previous pointer and the distance of un connected points.
                if (tmp->group == pinsGroup[currentGroup][0]->group && tmp->connected == false){
                    printf("Find %d/%d pin of group %d at (%d,%d)\n", numOfConnected, (int)pinsGroup[currentGroup].size(), currentGroup+1, tmp->x, tmp->y);
                    numOfConnected++;
                    tmp->traceBack( pinsGroup[currentGroup][0]->group );
                    if (numOfConnected == pinsGroup[currentGroup].size() ) {
                        routedSegment ++;
                    }
                    break;
                }
            }

            // if cannot find the pin untill the queue is empty
            // there are some nodes that's cannot reached 
            // this group of nodes can not route, 
            // remove current nodes.
            if ( queue->getSize() == 0 && numOfConnected < pinsGroup[currentGroup].size()) {
                printf("Group %d can not route\n",currentGroup +1 );
                //remove current connected pins of this group.
                resetConnected();
                break;
            }
            if (detail >=2 ) {
                updateGraph();
            }
        }
        
        // either the number achieved or the group can not be routed.
        // perform on the next group.
        currentGroup ++; 
    }
    if (detail ==1) {
        printf("Number of Routed:%d/%d\n",routedSegment,numGroups);
        printf("Wire length: %d\n",calWireLength());
    }
}

/* used when the desired pins not equal to the connected pins
   reset the previous Pointer of the whole map. */
void Circuit::resetPointer() {
    for (int i=0; i< xsize * ysize; i++ ) {
        NN[i].previous = NULL;
    }
}


// reset the distance for the unused pins
void Circuit::resetDistance() {
    for (int i=0; i< xsize * ysize; i++ ) {
        if(NN[i].connected == false){
            NN[i].distance = 9999;
            NN[i].cost = 9999;
        } 
    }
}

// if this group of pins cannot routes. disconnect all the previous connected.
void Circuit::resetConnected() {
    for (int i=0; i< xsize * ysize; i++) {
        if(NN[i].group == pinsGroup[currentGroup][0]->group) {            
            NN[i].connected = false;
            if(NN[i].isPin == false){
                NN[i].group =0;
            }
        }    
    }
}

void Circuit::pushBackConnected(Node* targetNode){
    for (int i=0; i< xsize * ysize; i++ ){
        if(NN[i].group == pinsGroup[currentGroup][0]->group && NN[i].connected== true) {
            NN[i].cost = 0;
            queue->enqueue(&NN[i],targetNode, drawflag);            
        }    
    }
}

void Circuit::initGraph(){
    Node * map = NN;
    char tmp[40] = "Capponcino routers";
    init_graphics(tmp);
    init_world(0,0,5+xsize*10, 5+ysize*10);
    setlinewidth(2);
    setlinestyle(SOLID);
    setcolor(BLACK);
    clearscreen();
}

void Circuit::updateGraph(){
    Node * map = NN;
    // char tmp[40] = "Latte routers";
    // strcpy(tmp,"Problem befoer solving");
    clearscreen();
    for(int i=0;i<=xsize;i++){
        drawline(2+i*10,2,2+i*10, 2+ysize*10);
    }
    for(int j=0;j<=ysize;j++){
        drawline(2,2+j*10,2+xsize*10,2+j*10);
    }

    for(int y=0;y<ysize;y++)
    {
        for(int x=0; x<xsize; x++)
        {
            int group = map[x + y*xsize].group;
            if (group !=0){
                drawBlock(x, y, group, map[x + y*xsize].isPin);
            }
        }    
    }    
    event_loop(button_press,drawscreen);
}

int Circuit::calWireLength(){
    int wireLength = 0;
    for (int i=0; i< xsize * ysize; i++) {
        if(NN[i].connected == true && NN[i].isPin == false) {            
            wireLength++;
        }    
    }
    return wireLength;
}

// pushback related to the enque, which related to the distance.
// resetDistance connected to the distance;