#include <bits/stdc++.h>
#include "Ring.h"
#include "global.h"
using namespace std;

string getRandomString() {
    string data = "";
    for (int i = 0; i < 10; i++) data+=(char)(rand()%26+'a');
    return data;
}

DataFrame Node::createFrame() {   // frameType is data only
    string data=getRandomString();
    srand(time(NULL));
    int destDevId = rand()%(ringsize);
    while(1) {
        if(destDevId!=deviceId) break;
        destDevId = rand()%(ringsize);
    }
    string destMac = devIdToMac[destDevId];
    DataFrame newframe('d', data, this->macAddress, destMac);
    return newframe;
}

void Node::sendFrame(DataFrame msg, int direction) {
    if(direction == -1) {   // choose shortest path
        int start = this->deviceId;
        int end = macToDevId[msg.receiverMac];
        int cwdist = (end-start+ringsize)%ringsize;
        int acwdist = ringsize - cwdist;
        direction =0;   // default direction is clockwise
        if(cwdist>acwdist) direction = 1;
    }
    if(direction==0) this->rightLink->transmitFrame(msg, direction);
    else this->leftLink->transmitFrame(msg, direction);
}

// Ack for token to be done

void Node::receiveFrame(DataFrame msg, int direction) {
    cout<<"DeviceID "<<deviceId<<": ";
    char msgType = msg.frameType;
    if(msgType == 'd') {
        if(msg.receiverMac == this->macAddress) {
            cout<<"MESSAGE RECEIVED"<<endl;
            DataFrame newack('a', "0", this->macAddress, msg.senderMac);
            this->sendFrame(newack, 1-direction);
        }
        else {
            cout<<"Message passed forward"<<endl;
            this->sendFrame(msg, direction);
        } 
    } 
    else if(msgType == 'a') {
        if(msg.receiverMac == this->macAddress) {
            cout<<"ACK RECEIVED"<<endl<<endl<<endl;
            int count = stoi(token.Data); // no of data packets has been transferred in the network
            count++;
            if(count>=MAX_TOKEN) return;   // Network terminated
            else {
                token.Data = to_string(count);
                token.senderMac = this->macAddress;
                token.receiverMac = this->rightLink->rightNode->macAddress;
                this->sendFrame(token, 0);
            }
        }
        else {
            cout<<"Ack passed forward"<<endl;
            this->sendFrame(msg, direction);
        } 
    }
    else {
        if(msg.receiverMac == this->macAddress) {
            DataFrame newframe = createFrame();
            cout<<"Token received."<<" New Frame created, sending to "<<macToDevId[newframe.receiverMac]<<endl;   
            // cout<<"             New Frame created. Send to "<<macToDevId[newframe.receiverMac]<<endl; 
            sendFrame(newframe, -1);    // direction should be decided by node in sendFrame function if set to -1
        }
    }
}