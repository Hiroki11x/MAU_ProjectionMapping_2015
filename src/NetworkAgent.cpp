//
//  NetworkAgent.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/13.
//
//
#include "NetworkAgent.h"

void NetworkAgent::moveToNextPosition(){
    position = nextPosition;
}

void NetworkAgent::validate(wstring agentName){
    name = agentName;
}

NetworkAgent::NetworkAgent(){
    noiseElementX = 0;
    noiseElementY = 0;
    position = ofVec2f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
    nextPosition = position;
}