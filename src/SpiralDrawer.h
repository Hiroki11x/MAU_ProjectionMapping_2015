//
//  SpiralDrawer.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/08.
//
//
#ifndef SpiralDrawer_h
#define SpiralDrawer_h

#include "ofMain.h"
#include "ofxAssimpModelLoaderExtend.h"

#define RECT_LENGTH 10
#define INTERVAL 50
#define RECT_WIDTH 200
#define RECT_HEIGHT 50

class SpiralDrawer {
public:
    ofxAssimpModelLoaderExtend model;
    ofMesh spiralMesh;
    ofVbo spiralVbo;
    
    
    void init(float scale);
    void drawSpiral(float t); //0=<t = 1
    
    ofMatrix4x4 modelMatrix; //.glscale
    
};
#endif
