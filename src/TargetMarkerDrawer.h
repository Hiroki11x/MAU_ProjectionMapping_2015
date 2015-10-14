//
//  TargetMarkerDrawer.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/14.
//
//

#ifndef TargetMarkerDrawer_h
#define TargetMarkerDrawer_h

#include "ofMain.h"
class TargetMarkerDrawer{
public:
    ofVboMesh insideDrawer;
    ofVboMesh outsideDrawer;
    
    float insideSpeed;
    float outsideSpeed;
    
    float insideDeg;
    float outsideDeg;
    
    void init(float radius);
    void drawTargetMarker();
};
#endif