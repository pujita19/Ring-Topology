#include <bits/stdc++.h>
#include "Ring.h"
using namespace std;

string decTohex(int n) {
    if(n<10) return to_string(n);
    if(n==10) return "A";
    if(n==11) return "B";
    if(n==12) return "C";
    if(n==13) return "D";
    if(n==14) return "E";
    return "F";
}

string getRandomMac() {
    srand(time(NULL));
    string mac="";
    while(1) {
        for(int i=0;i<6;i++) {
            mac+=decTohex(rand()%16);
            mac+=decTohex(rand()%16);
            if(i<5) mac+=':';
        }
        if(macToDevId.find(mac) == macToDevId.end()) break;
        else mac=="";
    }
    return mac;
}

void Ring::addNodeToNetwork() {
    string macAddress = getRandomMac();
    cout<<macAddress<<endl;
    devIdToMac[ringsize] = macAddress;
    macToDevId[macAddress] = ringsize;
    Node newNode(ringsize, macAddress);
    cout<<newNode.deviceId<<" "<<newNode.macAddress<<endl;
    cout<<&newNode<<endl;
    if(firstNode == NULL) {
        firstNode = &newNode;
        lastNode = &newNode;
        Link newLink(newNode, newNode);
        firstNode->rightLink = &newLink;
        firstNode->leftLink = &newLink;
    }
    else {
        // cout<<firstNode<<" "<<lastNode<<endl;
        Link newRightLink(*firstNode, newNode);
        Link newLeftLink(newNode,*lastNode);
        newNode.leftLink = &newLeftLink;
        newNode.rightLink = &newRightLink;
        firstNode->leftLink=&newRightLink;
        lastNode->rightLink=&newLeftLink;
        lastNode = &newNode;
        // cout<<firstNode<<" "<<lastNode<<endl;
    }
    ringsize++;
}

void Ring::startNetwork() {
    cout<<ringsize<<endl;
    // TEST NETWORK
    Node* noderef = firstNode;
    for(int i=0;i<ringsize;i++) {
        cout<<noderef<<" "<<noderef->rightLink<<endl;
        noderef = noderef->rightLink->rightNode;
    }
    token.receiverMac = devIdToMac[0];
    this->firstNode->receiveFrame(token, 0);
}