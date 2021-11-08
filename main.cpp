#include <bits/stdc++.h>
#include "Ring.cpp"
#include "Node.cpp"
#include "Link.cpp"
#include "global.h"

using namespace std;

int MAX_TOKEN = 4;  // total packets to transfer in network
int ringsize = 0;
DataFrame token('t',"0","","");
map<int,string>devIdToMac;
map<string,int>macToDevId;

int main() {
    Ring RingNetwork;    // creates network
    
    // add nodes
    RingNetwork.addNodeToNetwork();
    RingNetwork.addNodeToNetwork();
    // RingNetwork.addNodeToNetwork();
    // RingNetwork.addNodeToNetwork();

    RingNetwork.startNetwork();    // start network
} 