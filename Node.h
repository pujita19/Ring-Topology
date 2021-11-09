#include "DataFrame.h"
using namespace std;
#pragma once

class Link;

class Node {
    public:
    int deviceId;
    int countBroken;    // no.of time curr frame returned due to broken links
    DataFrame currframe;
    string macAddress;
    Link *rightLink;    // used to send the packet in clockwise direction
    Link *leftLink;    // used to send the packet in anti-clockwise direction
    // direction 0: clockwise, 1: anti-clockwise  
    Node(int deviceid, string macadd) {
        countBroken = 0;
        deviceId = deviceid;
        macAddress = macadd;
        rightLink = NULL;
        leftLink = NULL;
        currframe.frameType = '0';
        currframe.Data = "0";
        currframe.senderMac = macAddress;
        currframe.receiverMac = "0";
    }

    DataFrame createFrame();
    void passToken();
    void sendFrame(DataFrame msg, int direction);
    void receiveFrame(DataFrame msg, int direction);
};
