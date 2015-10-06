//
//  TrailRenderer.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/02.
//
//
#ifndef TrailRenderer_h
#define TrailRenderer_h

#include "ofMain.h"

class TrailRenderer{
public:
    enum TrailShape{
        SimpelSphere,
        SimpleBox,
        SimpleLine,
        MultiSphere,
        MultiBox
    };
    
    int trailNum;
    float degree;
    float endPosition;
    float position;
    float radius;
    float size;
    bool acceralateMode;
    bool convergenceMode;
    bool rotateMode;
    
    ofVec3f startPoint;
    ofVec3f targetPoint;
    TrailShape trailShape;
    
    void changeMode(bool rotate, bool convergence, bool acceralate);
    void drawTrailer();
    void update();
    
    TrailRenderer(ofVec3f sPoint, ofVec3f tPoint ,TrailShape shape = TrailShape::SimpelSphere, int trailNum = 4, float radius = 500);
    TrailRenderer(){};
};
#endif
