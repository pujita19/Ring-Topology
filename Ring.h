#include <bits/stdc++.h>
#include "Node.h"
#include "Link.h"
#include "DataFrame.h"
#include "global.h"
using namespace std;
#pragma once

class Ring {
    public:
    Node *firstNode;    // pointer to first node
    Node *lastNode;    // pointer to last node for easy access
    Ring() {
        firstNode = NULL;
        lastNode = NULL;
    }
    void addNodeToNetwork();    // create network
    void startNetwork(int startNode);     // creates token and send it to given start node to start the network
};
