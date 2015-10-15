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
    ofVboMesh frameMesh;
    ofVboMesh centerCircle;
    float centerDeg;
    GraphGuiDrawer graph;
    TargetMarkerDrawer marker;
    
    int frameCounter;
    
    bool drawCenterCircleMode = true;
    bool drawGraphMode = true;
    bool drawTargetMarkerMode = true;
    bool drawClockMode = true;

    float clockDeg[3];
};
#endif
