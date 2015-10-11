//
//  IconStream.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/11.
//
//
#ifndef IconStream_h
#define IconStream_h

#include "SceneElement.h"
#include "ofMain.h"
#include "JsonReceiver.h"
#include "ofxAssimpModelLoader.h"

#define MAX_ICON 18
#define ICON_SIZE 32

class IconStream : public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    vector<ofVboMesh> iconPoints;
    ofImage newIcon;
    ofxAssimpModelLoader doorModel;
    ofLight light;
    ofCamera camera;
    
    int iconNum;
    int spentFrames;
    float rotation;
    bool rotationMode;
    float doorDeg;
    float downSpeed[MAX_ICON * ICON_SIZE * ICON_SIZE];
    
    void drawDoor(float deg);
};
#endif