#include <bits/stdc++.h>
#include "Ring.cpp"
#include "Node.cpp"
#include "Link.cpp"
#include "global.h"

using namespace std;

int MAX_TOKEN = 3;  // total packets to transfer in network
int ringsize = 0;
DataFrame token('t',"0","","");
map<int,string>devIdToMac;
map<string,int>macToDevId;
int testcase = 0;

int main() {
    Ring RingNetwork;    // creates network
    
    // add nodes

    RingNetwork.addNodeToNetwork();
    RingNetwork.addNodeToNetwork();
    RingNetwork.addNodeToNetwork();
    RingNetwork.addNodeToNetwork();
    RingNetwork.addNodeToNetwork();
    RingNetwork.addNodeToNetwork();

    cout<<"\nCreated network with "<<ringsize<<" nodes\n";

    cout<<"\nBeginning Simulation...\n\n";

    // cout<<"[Test 1] Ideal simulation: \n";
    // RingNetwork.startNetwork(0);    // start network
    // cout<<"\n\n";

    // // For infinite simulation
    // int curr = MAX_TOKEN%ringsize;
    // while(1) {
    //     RingNetwork.startNetwork(curr);
    //     curr = (curr+MAX_TOKEN)%ringsize;
    // }

    // cout<<"[Test 2] Non existent destination simulation: \n";
    // testcase = 1;
    // RingNetwork.startNetwork(0);
    
    // cout<<"[Test 3] Single broken link: \n";
    // testcase = 2;
    // int brokenLink = 2;     // broken link from cw direction
    // Node* ptr = RingNetwork.firstNode;
    // while(brokenLink--) {
    //     ptr = ptr->rightLink->rightNode;
    // }
    // ptr->rightLink->isBroken = true;
    // RingNetwork.startNetwork(0);

    // 2 broken links and check network
    // node down


    return 0;
} 