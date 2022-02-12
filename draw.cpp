#include "draw.h"
extern "C" {
    #include "graphics.h"
}

void drawBlock(int x, int y, int idx, bool pin){
    // idx represent the order of the pin or the obstacle if the idx is -1;
    int color = (idx == -1) ? 1: (idx == 0)? 0: (4 + idx % 7);
    setcolor(color);
    fillrect(2 + x * 10, 2 + y * 10, 2 + (x + 1) * 10, 2 + (y + 1) * 10);
    if (pin){
        setfontsize(20);
        setcolor(1);
        char pinIdx[10];
        sprintf(pinIdx, "Pin:%d", idx);
        drawtext(7 + x * 10, 7 + y * 10, pinIdx, 10);
    }
}