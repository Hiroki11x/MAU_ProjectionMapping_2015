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
    int rotateFrame;
    int waitFrame;
    int garallyStripMode = 0;
    bool drawFPSAndSPFMode = false;
    bool drawNetworkLineMode = false;
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
    ofLight light;
    ofShader backShader;
    GarallySceneGuiDrawer gui;
    ofColor fpsColor = ofColor(100,255,255);
    ofColor garallyColor = ofColor(255, 255, 255 , 150);
    ofColor lineColor = ofColor(0, 255, 255, 150);
    ofColor networkLineColor = ofColor(255,0,255);
    ofVboMesh networkLine;

    void initLineEmitPoints();
    void initModelDrawer();
    void updateNetworkLine();
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
    
    GLushort netLinePattern = 0x0000;
};
#endif