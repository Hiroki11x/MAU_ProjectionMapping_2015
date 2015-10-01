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
#include "UserAgentManager.h"

class SpyMesh : public SceneElement {
public:
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    virtual void onMouseDown(int x,int y) override;
    
    ofxAssimpModelLoaderExtend model;
    ofMesh mesh;
    ofLight	light;
    UserAgentManager agents;
    
    int mouseX,mouseY;
    int spentFrames;
    bool bAnimate;
    bool bAnimateMouse;
    float animationPosition;
    string text;
    string loadText(string filename){
        cout << filename;
        return string( ofBufferFromFile( filename ) );
    }
    vector<ofVec3f> vertx[7];
    vector<int> vertexAmount[7];
    vector< vector<int> > connection[7];
};
#endif
