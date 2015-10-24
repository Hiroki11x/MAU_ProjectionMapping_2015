//
//  GarallySceneGuiDrawer.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/15.
//
//
#ifndef GarallySceneGuiDrawer_h
#define GarallySceneGuiDrawer_h

#include "ofMain.h"
#include "GraphGuiDrawer.h"
#include "TargetMarkerDrawer.h"

class GarallySceneGuiDrawer{
public:
    void init();
    void drawGui();
    void update();
    void initFrame();
    void initCenterCircle();
    void drawClock();
    
    int frameCounter;
    bool drawCenterCircleMode = true;
    bool drawGraphMode = true;
    bool drawTargetMarkerMode = true;
    bool drawClockMode = true;
    float centerDeg;
    float clockDeg[3];
    
    ofVboMesh frameMesh;
    ofVboMesh centerCircle;
    GraphGuiDrawer graph;
    TargetMarkerDrawer marker;
    ofTrueTypeFont font;
    ofColor frameMeshColor = ofColor(0,200,200, 180);
    ofColor backCrossColor = ofColor(10, 255, 255, 60);
    ofColor centerCircleColor = ofColor(153,255,255,150);
    ofColor clockBackColor = ofColor(0,255,200,100);
    ofColor clockFrameColor = ofColor(0,255,200,100);
    ofColor clockDegColor = ofColor(50,255,255,180);
    ofColor clockCircleColor = ofColor(153,255,255,150);
    ofColor clockLineColor = ofColor(25,255,255,180);
    ofColor targetColor = ofColor(0,255,255);
    ofColor graphBackColor = ofColor(10,18,10,50);
    ofColor graphStringColor = ofColor(10,255,200,100);
    ofColor graphBarColor = ofColor(10,255,255,150);
    
};
#endif
