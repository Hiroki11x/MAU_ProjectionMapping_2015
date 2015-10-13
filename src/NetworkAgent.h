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
    ofVec2f position;
    ofVec2f nextPosition;
    vector<float> NorP;
    wstring name;
    
    float noiseElementX,noiseElementY;
    int index;
    
    void updatePosition();
    void moveToNextPosition();
    void validate(wstring agentName);
    
    NetworkAgent();
};
#endif
