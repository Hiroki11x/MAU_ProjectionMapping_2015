//
//  DrawerSphere.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/05.
//
//
#ifndef DrawerSphere_h
#define DrawerSphere_h

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class DrawerSphere {
public:
    ofxAssimpModelLoader model;
    void drawSphere(ofVec3f position, float scale);
    DrawerSphere(float scale);
    DrawerSphere(){};
private:
    void drawSphere(ofVec3f position);
};
#endif