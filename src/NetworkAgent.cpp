//
//  NetworkAgent.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/13.
//
//
#include "NetworkAgent.h"

void NetworkAgent::updatePosition(){
    nextPosition = position;
   /* nextPosition.x += (-0.5 + ofNoise(noiseElementX))* 2.0;
    nextPosition.x += ofRandom(-2.0,2.0);
    noiseElementX += ofRandom(1.0);
    nextPosition.y += (-0.5 + ofNoise(noiseElementY))* 2.0;
    nextPosition.y += ofRandom(-2.0,2.0);
    noiseElementY += ofRandom(1.0);*/

}

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