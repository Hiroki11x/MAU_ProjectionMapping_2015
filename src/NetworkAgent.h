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

#define STABLE_AGENTS_DISTANCE 100.0

class NetworkAgent {
public:
    int moveFrame;
    ofVec3f position;
    ofVec3f nextPosition;
    ofVec3f befPosition;
    vector<float> NorP;
    wstring name;
    
    void validate(wstring agentName);
    NetworkAgent();
};
#endif
