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

class SpyMeshIntro : public SceneElement {
public:
    
    int spentFrames;
    bool start;
    
    SceneManager manager;
    ModelDrawer garallyModelDrawer;
    ofxAssimpModelLoaderExtend model;
    ofVec3f targetVec;
    ofVec3f fireVec;
    //ofEasyCam camera;
    ofCamera camera;
    
    virtual void draw() override;
    virtual void update() override;
    virtual void init() override;
    virtual void onMouseDown(int x,int y) override;
    
    SpyMeshIntro(SceneManager Manager){
        this->manager = Manager;
    };
    
    float dis = 100000;
    ofVec3f rightTop = ofVec3f(dis,dis,0);
    ofVec3f leftTop = ofVec3f(- dis,dis,0);
    ofVec3f rightBottom = ofVec3f(dis,- dis,0);
    ofVec3f leftBottom = ofVec3f(-dis,- dis,0);
    ofVec3f fromVec[4] = {rightTop,leftTop,rightBottom,leftBottom};

};

#endif /* SpyMeshIntro_hpp */
