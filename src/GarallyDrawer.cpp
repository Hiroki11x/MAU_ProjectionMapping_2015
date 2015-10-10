//
//  GarallyDrawer.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/09.
//
//

#include "GarallyDrawer.h"

void GarallyDrawer::init(float scale){

    model.loadModel("garally.stl");
    model.setScale(scale, scale, scale);
}

void GarallyDrawer::drawGarally(){

    ofPushStyle();
    model.setPosition(7000 * sin((float)ofGetElapsedTimeMillis()/2000.0),
                      7000 * cos((float)ofGetElapsedTimeMillis()/1000.0),
                      0);
    if(ofGetElapsedTimeMillis() % 10 == 0){
        patternIndex = ofRandom(0,8);
    }
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1 , patterns[patternIndex]);
    ofSetColor(255);
    model.drawWireframe();
    glDisable(GL_LINE_STIPPLE);
    ofPopStyle();
}