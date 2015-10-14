//
//  SpyMeshIntro.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/02.
//
//
#ifndef SpyMeshIntro_h
#define SpyMeshIntro_h

#include "SceneElement.h"
#include "ModelDrawer.h"
#include "ofxAssimpModelLoaderExtend.h"
#include "SceneManager.h"
#include "TrailRenderer.h"
#include "JsonReceiver.h"

#define ADD_TRIANGLE_PER_UPDATE 7

class SpyMeshIntro : public SceneElement {
public:
    
    virtual void draw() override;
    virtual void update() override;
    virtual void init() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;

    int spentFrames;
    bool isStarted;
    float lineEmitPointDistance;
    
    TrailRenderer trails;
    ModelDrawer garallyModelDrawer;
    ofxAssimpModelLoaderExtend model;
    ofVec3f targetPoint;
    ofVec3f emitPoint;
    ofVec3f lineEmitPoints[4];
    ofCamera camera;
    
    void initLineEmitPoints();
    void initModelDrawer();
    void reset();
};
#endif