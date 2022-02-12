#pragma once
#include "Node.h"
// #include "Circuit.h"
extern "C" {
    #include "graphics.h"
}

// void initGraph(Circuit circuit);
// void updateGraph(Circuit circuit);
// void updateBlock(Node * node);
void drawBlock(int x, int y, int idx, bool pin);
static void button_press(float x,float y){}
static void drawscreen(void){}