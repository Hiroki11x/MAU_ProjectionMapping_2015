//
//  NetworkAgent.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/13.
//
//
#ifndef NetworkAgent_h
#define NetworkAgent_h

#include "ofMain.h"

class NetworkAgent {
public:
    ofVec2f possition;
    vector<NetworkAgent> connectedAgents;
    wstring name;
    
    void updatePosition();
};
#endif
