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
    wait += 0.1;
    if(wait > interval){
        wait = 0;
        writeText = !writeText;
    }
    if(writeText){
        ofDrawBitmapString(text, ofGetWidth()/2 - 100, ofGetHeight()/2 + 40);
    }
    ofDrawBitmapString("Plaese Tweet with #MAU", ofGetWidth()/2 - 100, ofGetHeight()/2 - 50, 100);
    
    barLength += 1;
    if(barLength >= 400){
        barLength = 0;
    }
   
    ofFill();
    ofRect(ofGetWidth()/2 - 200, ofGetHeight()/2 - 10,
           barLength, 20);
    
    ofPopStyle();
}

void Loading::update(){}