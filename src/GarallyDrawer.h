//
//  GarallyDrawer.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/09.
//
//

#ifndef GarallyDrawer_h
#define GarallyDrawer_h

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class GarallyDrawer {
public:
    ofxAssimpModelLoader model;
    
    void drawGarally();
    void init(float scale = 50);
    int patternIndex;
    float noiseElement;

    GLushort patterns[8] = {
        0x5555,
        0x1234,
        0x7333,
        0x4113,
        0x2335,
        0x7422,
        0x1323,
        0x1111
    };
};
#endif
