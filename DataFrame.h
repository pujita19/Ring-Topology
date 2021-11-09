#include <bits/stdc++.h>
using namespace std;
#pragma once

class DataFrame {
    public:
    char frameType; // a-ack d-data t-token b-brocken link seen
    string Data;
    string senderMac;
    string receiverMac;
    
    DataFrame() {
        frameType = '0';
        Data = "0";
        senderMac = "0";
        receiverMac ="0";
    }

    DataFrame(char frametype, string data, string sendermac, string recmac){
        frameType = frametype;
        Data = data;
        senderMac = sendermac;
        receiverMac = recmac;
    }
};
