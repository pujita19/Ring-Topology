#include "DataFrame.h"
using namespace std;
#pragma once

class Link;

class Node {
    public:
    int deviceId;
    string macAddress;
    Link *rightLink;    // used to send the packet in clockwise direction
    Link *leftLink;    // used to send the packet in anti-clockwise direction
    // direction 0: clockwise, 1: anti-clockwise  
    Node(int deviceid, string macadd) {
        deviceId = deviceid;
        macAddress = macadd;
        rightLink = NULL;
        leftLink = NULL;
    }

    DataFrame createFrame();     // shortest path is not considered yet
    void sendFrame(DataFrame msg, int direction);
    void receiveFrame(DataFrame msg, int direction);
};
