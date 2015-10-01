//
//  BuildPC.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#include "BuildPC.h"

void BuildPC::update(){
    waitFrame++;
    if(waitFrame > intervalFrame){
        displayText += buildTexts.at(textIndex).text;
        intervalFrame = buildTexts.at(textIndex).interval;
        waitFrame = 0;
        if(textIndex < buildTexts.size() - 1){
            textIndex++;
        }
    }
}

void BuildPC::draw(){
    ofPushStyle();
    ofSetColor(50, 255, 50);
    drawer.drawString(displayText, 50, 100);
    ofPopStyle();
}
