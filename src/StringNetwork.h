//
//  StringNetwork.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/13.
//
//
#ifndef StringNetwork_h
#define StringNetwork_h

#include "SceneElement.h"
#include "ofxTrueTypeFontUL2.h"
#include "NetworkAgent.h"
#include "JsonReceiver.h"

#define MAX_AGENTS 50

class StringNetwork :public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    int cameraRotateFrames;
    int rotateFrame;
    int waitFrame;
    int agentNum;
    int fontSize;
    int spentFrames;
    float expandingArea;
    float cameraZ;
    ofxTrueTypeFontUL2 font;
    ofEasyCam camera;
    ofShader backShader;
    ofVec3f cameraPosition;
    ofVec3f befCameraPosition;
    ofVec3f nextCameraPosition;
    ofVec3f cameraLookPoint;
    ofVec3f befCameraLookPoint;
    ofVec3f nextCameraLookPoint;
    //ofVboMesh backGroundCrosses;
    vector<NetworkAgent> networkAgents;
    
    void updateAgents();
};
#endif

