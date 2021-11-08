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

    cout<<"[Test 1] Ideal simulation: \n";
    RingNetwork.startNetwork();    // start network
    cout<<"\n\n";

    cout<<"[Test 2] Non existent destination simulation: \n";
    testcase = 1;
    RingNetwork.startNetwork();
    
    // 1 broken link
    // 2 broken links and check network
    // node down

    return 0;
} 