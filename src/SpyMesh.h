//
//  SpyMesh.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//

#ifndef SpyMesh_h
#define SpyMesh_h

#include "ofMain.h"
#include "SceneElement.h"
#include "TrianglePoints.h"
#include "LinePoints.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"

#define NUM_BALL 80

class SpyMesh : public SceneElement {
public:
    
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    virtual void onMouseDown(int x,int y) override;
    
    ofxAssimpModelLoader model;
    ofMesh mesh;
    ofLight	light;
    int mouseX,mouseY;
    
    bool bAnimate;
    bool bAnimateMouse;
    float animationPosition;
    
};

#endif