#include <bits/stdc++.h>
using namespace std;
#pragma once

class DataFrame {
    public:
    char frameType; // a-ack d-data t-token
    string Data;
    string senderMac;
    string receiverMac;
    
    DataFrame(char frametype, string data, string sendermac, string recmac){
        frameType = frametype;
        Data = data;
        senderMac = sendermac;
        receiverMac = recmac;
    }
};
