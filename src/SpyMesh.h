//
//  SpyMesh.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#ifndef SpyMesh_h
#define SpyMesh_h
#define NUM_BALL 80

#include "ofMain.h"
#include "SceneElement.h"
#include "TrianglePoints.h"
#include "LinePoints.h"
#include "ofxAssimpModelLoaderExtend.h"
#include "ofVboMesh.h"
#include "ModelDrawer.h"
#include "UserAgent.h"

class SpyMesh : public SceneElement {
public:
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void onMouseDown(int x,int y) override;
    
    ofxAssimpModelLoaderExtend model;
    ofMesh mesh;
    ofLight	light;
    ofSoundPlayer soundPlayer;
    ofEasyCam camera;
    ofVec3f targetVec;
    ofVec3f fireVec;
    UserAgent agents[4];
    ModelDrawer modelDrawer;
    ModelDrawer garallyModelDrawer;
    
    int mouseX,mouseY;
    int spentFrames;
    float modelSize;
    float animationPosition;
    bool bAnimate;
    bool bAnimateMouse;
    bool button = false;

    string text;
    string loadText(string filename){
        cout << filename;
        return string( ofBufferFromFile( filename ) );
    }
    
    float dis = 200;
    ofVec3f rightTop = ofVec3f(dis,dis,0);
    ofVec3f leftTop = ofVec3f(- dis,dis,0);
    ofVec3f rightBottom = ofVec3f(dis,- dis,0);
    ofVec3f leftBottom = ofVec3f(-dis,- dis,0);
    ofVec3f fromVec[4] = {rightTop,leftTop,rightBottom,leftBottom};
};
#endif
