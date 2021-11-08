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
        if(macToDevId.find(mac)==macToDevId.end()) break;
        else mac="";
    }
    return mac;
}

void Ring::addNodeToNetwork() {
    string macAddress = getRandomMac();
    devIdToMac[ringsize] = macAddress;
    macToDevId[macAddress] = ringsize;
    Node* newNode = new Node(ringsize, macAddress);
    if(firstNode == NULL) {
        firstNode = newNode;
        lastNode = newNode;
        Link* newLink = new Link(*newNode, *newNode);
        firstNode->rightLink = newLink;
        firstNode->leftLink = newLink;
    }
    else {
        Link* newRightLink = new Link(*firstNode, *newNode);
        Link* newLeftLink = new Link(*newNode,*lastNode);
        newNode->leftLink = newLeftLink;
        newNode->rightLink = newRightLink;
        firstNode->leftLink=newRightLink;
        lastNode->rightLink=newLeftLink;
        lastNode = newNode;
    }
    ringsize++;
}

void Ring::startNetwork() {
    token.Data = "0";
    token.receiverMac = devIdToMac[0];
    this->firstNode->receiveFrame(token, 0);
}