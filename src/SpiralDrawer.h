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

class SpiralDrawer {
public:
    ofxAssimpModelLoaderExtend model;

    void init(float scale);
    void drawSpiral(float t);
};
#endif
