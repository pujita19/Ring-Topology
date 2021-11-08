#include <bits/stdc++.h>
#include "DataFrame.h"
using namespace std;
#pragma once

extern int MAX_TOKEN;
extern int ringsize;
extern map<int,string>devIdToMac;   
extern map<string,int>macToDevId;
extern DataFrame token; // Data in token stored no of packets created 
extern int testcase;    // 0: ideal 1: non existent destination 