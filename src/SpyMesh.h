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
#include "SoundManager.h"
#include "JsonReceiver.h"
#include "ofxRollingCam.h"
#include "RandomTriangleDrawer.h"
#include "AgentAnalysis.h"
#include "SpiralDrawer.h"
#include "GarallyDrawer.h"
#include "GraphGuiDrawer.h"
#include "SpyMeshSceneGui.h"

#define ADD_TRIANGLE_PER_TWEET 50
#define ADD_TRIANGLE_PER_AGENT_TRIANGLE 0.2

class SpyMesh : public SceneElement {
public:
    
    virtual void draw() override;
    virtual void init() override;
    virtual void stop() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    ofxAssimpModelLoaderExtend model;
    ofMesh mesh;
    ofLight	light;
    ofEasyCam camera;
    ofVec3f targetPoint;
    ofVec3f emitPoint;
    ofVec3f lineEmitPoints[6];
    ModelDrawer modelDrawer;
    DrawerSphere sphere;
    RandomTriangleDrawer rtDrawer;
    ofxRollingCam rollCam;
    SpiralDrawer spiralDrawer;
    GarallyDrawer garallyDrawer;
    ofShader backShader;
    vector<AgentAnalysis> agents;
    SpyMeshSceneGui gui;

    int mouseX,mouseY;
    int spentFrames;
    int wainingFrames;
    int agentNum;
    float modelSize;
    float lineEmitPointDistance;
    bool useRollCam = false;
    bool modelDrawMode = true;
    bool coloerMeshDrawMode = false;
    bool randomTrianlgeDrawMode = false;
    bool garallyDrawMode = false;
    bool randomExpandMeshDrawMode = false;
    bool agentDebug = false;
    bool trailMode = false;
    
    void initLineEmitPoints();
    void initModelDrawer();
    void drawEmitter();
    void updateVertices();
    void reset();
};
#endif