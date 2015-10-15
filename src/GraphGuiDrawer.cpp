//
//  GraphGuiDrawer.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/15.
//
//
#include "GraphGuiDrawer.h"

void GraphGuiDrawer::drawGraphGui(){
    ofDisableDepthTest();
    //graphBack.begin();
    ofSetColor(0,30,30);
    ofRect(0, 0, scale.x, scale.y);
    //graphBack.end();
    
    switch (mode) {
        case RECT_BAR:
            drawRectBarGraph();
            break;
        case WAVE:
            drawWaveGraph();
            break;
        case CIRCLE:
            drawCircleGraph();
            break;
        default:
            break;
    }
}

void GraphGuiDrawer::drawRectBarGraph(){
    ofSetColor(0, 100, 100);
    for(int i = 0; i < graphNum; i++){
        ofRect(16,16 + 27 * i,
               15 + graphParamatar[i], 12);
    }
}

void GraphGuiDrawer::drawWaveGraph(){}

void GraphGuiDrawer::drawCircleGraph(){}

void GraphGuiDrawer::updateGraphParams(){
    for(int i = 0; i < 5; i++){
        graphParamatar[i] += ofRandom(-2.0, 2.0);
    }
}

GraphGuiDrawer::GraphGuiDrawer(ofVec2f scale){
    this-> scale = ofVec2f(300, 100);
    graphNum = 3;
    for(int i = 0; i < 5; i++){
        graphParamatar[i] += ofRandom(0,100);
    }
    mode = RECT_BAR;
}