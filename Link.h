#include <bits/stdc++.h>
#include "DataFrame.h"
#include "Node.h"
using namespace std;
#pragma once

class Link {
    public:
    bool isBroken;
    Node *rightNode;    // next node to send packet if packet is been sent in clockwise direction
    Node *leftNode;    // next node to send packet if packet is been sent in anti-clockwise direction
    Link(Node &firstNode, Node &newNode) {
        isBroken = false;
        rightNode = &firstNode;
        leftNode = &newNode;
    }

    // direction 0: clockwise 1: anti-clockwise  
    void transmitFrame(DataFrame msg, int direction);
};
