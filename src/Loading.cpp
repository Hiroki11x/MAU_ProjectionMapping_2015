//
//  Loading.cpp
//  MauInteractive
//
//  Created by SakuragiYoshimasa on 2015/09/25.
//
//
#include "Loading.h"

void Loading::draw(){
    
    ofPushStyle();

    ofSetColor(50,255,50);
    if(writeText){
        drawer.drawString(text, ofGetWidth()/2 - 150, ofGetHeight()/2 + 60);
    }
    drawer.drawString("Plaese Tweet with #MAU", ofGetWidth()/2 - 250, ofGetHeight()/2 - 60);
    ofFill();
    ofRect(ofGetWidth()/2 - 300, ofGetHeight()/2 - 10,barLength, 20);
    
    ofPopStyle();
}

void Loading::update(){
    wait += 0.1;
    if(wait > interval){
        wait = 0;
        writeText = !writeText;
    }
    barLength += 1;
    if(barLength >= 600){
        barLength = 0;
    }
}