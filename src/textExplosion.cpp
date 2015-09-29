//
//  textExplosion.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//

#include "textExplosion.h"

void textExplosion::update(){
    waitFrame++;
    if(waitFrame < drawFrame){
        if(waitFrame % 4 == 0){
            text += "asdfghjkllllkjhgfdsdfgfhjfgbfcb";
        }
        if(waitFrame % 5 == 0){
            text += "\n";
        }
    }
}

void textExplosion::draw(){
    drawer.drawString(text, ofRandom(-100,ofGetWidth() + 50), ofRandom(-100,ofGetHeight() + 50));
}

void textExplosion::init(){
    ofSetColor(50,255,50);
    ofSetBackgroundAuto(false);
}

void textExplosion::end(){
    ofSetBackgroundAuto(true);
}

