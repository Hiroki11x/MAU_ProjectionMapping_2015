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
#include "GarallySceneGuiDrawer.h"

#define ADD_TRIANGLE_PER_UPDATE 7

class SpyMeshIntro : public SceneElement {
public:
    
    virtual void draw() override;
    virtual void update() override;
    virtual void init() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;

    int spentFrames;
    int cameraRotateFrames;
    float lineEmitPointDistance;
    
    TrailRenderer trails;
    ModelDrawer garallyModelDrawer;
    ofxAssimpModelLoaderExtend model;
    ofVec3f targetPoint;
    ofVec3f emitPoint;
    ofVec3f lineEmitPoints[4];
    ofVec3f cameraTarget;
    ofCamera camera;
    ofVec3f cameraPosition;
    ofVec3f befCameraPosition;
    ofVec3f nextCameraPosition;
    ofVec3f cameraLookPoint;
    ofVec3f befCameraLookPoint;
    ofVec3f nextCameraLookPoint;
    ofVec2f fpsPoint;
    int rotateFrame;
    int waitFrame;
    ofLight light;
    ofShader backShader;
    GarallySceneGuiDrawer gui;
    bool drawFPSAndSPFMode = true;
    int garallyStripMode = 0;
    
    void initLineEmitPoints();
    void initModelDrawer();
    void reset();
    
    GLushort pattern[8] = {
        0x0003,
        0x000C,
        0x0030,
        0x00C0,
        0x0300,
        0x0F00,
        0x3000,
        0xF000
    };
};
#endif