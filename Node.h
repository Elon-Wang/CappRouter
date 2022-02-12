#pragma once
#include <bits/stdc++.h>
#include "draw.h"

struct Node
{
    /* data */
    int idx, x, y;
    int distance = 9999;
    int value = 9999;
    int cost = 9999;
    int group = 0;
    Node* previous = NULL;
    bool isPin = false;
    bool connected = false;

    Node(){};
    Node(int a, int xsize, int ysize): idx(a)
    {
        x = idx % xsize; 
        y = idx / xsize;
    }

    void traceBack(int groupIdx);
    void updateBlock();
    // bool available(Node * prev, int xBound, int yBound, int groupIdx);
};