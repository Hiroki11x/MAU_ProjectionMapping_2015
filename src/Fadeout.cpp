//
//  Fadeout.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#include "Fadeout.h"

void Fadeout::update(){
    waitTime++;
}

void Fadeout::draw(){
    ofSetColor(50.0 * (1.0 - waitTime / fadeTime), 255.0 * ( 1.0 - waitTime / fadeTime), 50.0 * ( 1.0 - waitTime / fadeTime));
    ofRect(0,0,ofGetWidth(),ofGetHeight());
}
