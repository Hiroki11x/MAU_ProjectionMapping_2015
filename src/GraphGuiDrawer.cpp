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
    ofSetColor(0,30,30);
    ofRect(0, 0, scale.x, scale.y);

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
    
    for(int i = 0; i < graphNum; i++){
        ofSetColor(100, 180, 150);
        ofDrawBitmapString(ofToString(i + 1) + ofToString(graphParamatar[i]),5, 27 + 27 * i );
        ofSetColor(0, 100, 100);
        ofRect(50,16 + 27 * i,
               graphParamatar[i], 12);
    }
}

void GraphGuiDrawer::drawWaveGraph(){}

void GraphGuiDrawer::drawCircleGraph(){}

void GraphGuiDrawer::updateGraphParams(){
    for(int i = 0; i < 5; i++){
        graphParamatar[i] += ofRandom(-10.0, 10.0);
        if(graphParamatar[i] < 0){
            graphParamatar[i] = 0;
        }else if (graphParamatar[i] > 240){
            graphParamatar[i] = 240;
        }
    }
}

GraphGuiDrawer::GraphGuiDrawer(){
    this-> scale = ofVec2f(300, 100);
    graphNum = 3;
    for(int i = 0; i < 5; i++){
        graphParamatar[i] += ofRandom(0,100);
    }
    mode = RECT_BAR;
    font = new ofxTrueTypeFontUL2();
    font->loadFont("Fonts/Futura.ttc",32,true,true,0.3f,0,true);
    font->loadSubFont("Fonts/Gidole-Regular.ttf");
    font->loadSubFont("Fonts/FiraCode-Regular.otf");
    font->loadSubFont("Yumincho");
    font->loadSubFont(OF_TTF_SERIF,1.2,-0.02);
    font->loadSubFont("Geeza Pro",1,-0.04,0x0600,0x06FF,"arab");
    font->useProportional(true);
    font->useVrt2Layout(true);
    font->setLineHeight(font->getFontSize()*1.5);
}