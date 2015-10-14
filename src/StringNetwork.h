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

#define MAX_AGENTS 40

class StringNetwork :public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    ofxTrueTypeFontUL2 font;
    ofCamera camera;
    ofLight light;
    vector<NetworkAgent> networkAgents;
    
    int agentNum;
    int fontSize;
    int spentFrames;
    float expandingArea;
    float cameraZ;
   
    void updateAgents();
};
#endif

