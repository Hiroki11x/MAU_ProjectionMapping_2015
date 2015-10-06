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
#include "ofxAssimpModelLoaderExtend.h"
#include "ofVboMesh.h"
#include "ModelDrawer.h"
#include "DrawerSphere.h"

#define ADD_TRIANGLE_PER_UPDATE 2

class SpyMesh : public SceneElement {
public:
    
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    ofxAssimpModelLoaderExtend model;
    ofMesh mesh;
    ofLight	light;
    ofSoundPlayer soundPlayer;
    ofEasyCam camera;
    ofVec3f targetPoint;
    ofVec3f emitPoint;
    ofVec3f lineEmitPoints[4];
    ModelDrawer modelDrawer;
    DrawerSphere sphere;
    
    int mouseX,mouseY;
    int spentFrames;
    int wainingFrames;
    float modelSize;
    float lineEmitPointDistance;
    bool isStarted = false;
    
    void initLineEmitPoints();
    void initModelDrawer();
    void drawEmitter();
};
#endif
