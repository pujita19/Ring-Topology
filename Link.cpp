#include <bits/stdc++.h>
#include <unistd.h>
#include "Link.h"
#include "Node.h"
using namespace std;

void Link::transmitFrame(DataFrame msg, int direction) {
    if(direction==0) (this->rightNode)->receiveFrame(msg, direction);
    else (this->leftNode)->receiveFrame(msg,direction);
}