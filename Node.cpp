#include <bits/stdc++.h>
#include "Ring.h"
#include "global.h"
using namespace std;

string getRandomString() {
    string data = "";
    for (int i = 0; i < 10; i++) data+=(char)(rand()%26+'a');
    return data;
}

void Node::passToken() {
    if(this->rightLink->isBroken) {
        cout<<"DeviceID "<<deviceId<<": ";
        cout<<"Token can't be passed to next node\n"<<endl;
        cout<<"Network terminated\n";
        return;
    }
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

DataFrame Node::createFrame() {   // frameType is data only
    string data=getRandomString();
    srand(time(NULL));
    int destDevId = rand()%(ringsize);
    while(1) {
        if(destDevId!=deviceId) break;
        destDevId = rand()%(ringsize);
    }
    string destMac = devIdToMac[destDevId];

    if(testcase == 1) {
        int pfactor = 3;    // probability of non existence destination would be 1/pfactor
        int x = (rand()+stoi(token.Data))%pfactor;
        if(x==0) destMac = "00";   // non existence mac address
    } 

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
    if(direction==0) {
        if(this->rightLink->isBroken) {
            msg.frameType = 'b';
            msg.Data = "Link between " + to_string(deviceId)  + " " + to_string((deviceId+1)%ringsize)+" is broken";
            msg.receiverMac = msg.senderMac;
            msg.senderMac = this->macAddress;
            this->leftLink->transmitFrame(msg, 1-direction);
        }
        else this->rightLink->transmitFrame(msg, direction);
    } 
    else {
        if(this->leftLink->isBroken) {
            msg.frameType = 'b';
            msg.Data = "Link between " + to_string((deviceId-1+ringsize)%ringsize)  + " " + to_string(deviceId)+" is broken";
            msg.receiverMac = msg.senderMac;
            msg.senderMac = this->macAddress;
            this->rightLink->transmitFrame(msg, 1-direction);
        }
        else this->leftLink->transmitFrame(msg, direction);
    } 
}

// Ack for token to be done

void Node::receiveFrame(DataFrame msg, int direction) {
    cout<<"DeviceID "<<deviceId<<": ";
    char msgType = msg.frameType;
    if(msgType == 'b') {
        if(msg.receiverMac == this->macAddress) {
            cout<<msg.Data<<endl;
            cout<<"DeviceID "<<deviceId<<": ";
            cout<<"Message transmiting in opposite direction"<<endl;
            msg.Data = currframe.Data;
            msg.frameType = currframe.frameType;
            msg.receiverMac = currframe.receiverMac;
            msg.senderMac = currframe.senderMac;
            this->sendFrame(msg, direction);
        } 
        else {
            cout<<"Message passed forward"<<endl;
            this->sendFrame(msg, direction);
        }
    }
    else if(msgType == 'd') {
        if(msg.senderMac == this->macAddress) {
            cout<<"Destination device not found\n\n";     
            // eg: a node (printer) got deleted from network but routing table isn't upto date.
            // node has to trouble shoot 
            this->passToken();
        }
        else if(msg.receiverMac == this->macAddress) {
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
            cout<<"ACK RECEIVED"<<endl<<endl;
            this->passToken();
        }
        else {
            cout<<"Ack passed forward"<<endl;
            this->sendFrame(msg, direction);
        } 
    }
    else {
        if(msg.receiverMac == this->macAddress) {
            DataFrame newframe = createFrame();
            currframe.Data = newframe.Data;
            currframe.frameType = newframe.frameType;
            currframe.receiverMac = newframe.receiverMac;
            currframe = newframe;
            int destId = 0;
            if(macToDevId.find(newframe.receiverMac) != macToDevId.end()) destId = macToDevId[newframe.receiverMac];
            else destId = ringsize + rand()%3;
            cout<<"Token received."<<" New Frame created, sending to "<<destId<<endl;   
            sendFrame(newframe, -1);    // direction should be decided by node in sendFrame function if set to -1
        }
    }
}