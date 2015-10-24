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

#define SCALE_RATE 1.4

class TargetMarkerDrawer{
public:
    enum Mode{
        ROTATE,
        STOP,
        ROTATE_REVERSE,
        STOP2,
        END
    };
    
    int frameCount;
    int modeFrames[5];
    float insideSpeed = 5.0;
    float outsideSpeed = -3.0;
    float insideDeg;
    float outsideDeg;
    
    ofVboMesh insideDrawer;
    ofVboMesh outsideDrawer;
    ofVec2f position;
    Mode mode = ROTATE;
        
    void init(float radius);
    void update();
    void drawTargetMarker(ofColor tColor);
    void restart();
};
#endif