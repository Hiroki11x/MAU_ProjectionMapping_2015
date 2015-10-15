//
//  FoundationDrawer.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/15.
//
//

#ifndef FoundationDrawer_h
#define FoundationDrawer_h

#include "ofMain.h"

#define MIDDLE_RATE 1.15
#define OUTSIDE_RATE 1.65

class FoundationDrawer{
public:
    void init(float radius);
    void drawFoundation();
    void update();
    
    ofShader lightShader;
    ofVboMesh insideCircleMesh;
    ofVboMesh middleCircleMesh;
    ofVboMesh outsideCircleMesh;
    
    float insideSpeed = -5.0;
    float middleSpeed = 8.0;
    float outsideSpeed = 1.0;
    float insideDeg;
    float middleDeg;
    float outsideDeg;
};
#endif
