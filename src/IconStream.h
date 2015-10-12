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
    enum Mode{
        LoadIcon,
        MakeCircle,
        Convergence,
        End,
        Down
    };
    
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
    Mode mode;
    ofVec3f lastPosition;
    ofVec3f lastParticlePosition;
    ofVec3f targetPosition[MAX_ICON * ICON_SIZE * ICON_SIZE];
    ofVec3f cameraPosition;
    
    int iconNum;
    int spentFrames;
    float rotation;
    bool rotationMode;
    bool drawWhiteRect;
    float doorDeg;
    float downSpeed[MAX_ICON * ICON_SIZE * ICON_SIZE];
    
    void drawDoor(float deg);
    void loadIcon();
    void makeCircle();
    void convergence();
    void reconvergence();
    void down();
};
#endif