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

#define SPY_ICON_SIZE 4
#define MAX_ICON 16
#define ICON_SIZE 32

class IconStream : public SceneElement {
public:
    enum Mode{
        LoadIcon,
        MakeCircle,
        Convergence,
        RemakeCircle,
        Down,
        RemakeIcon
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
    ofColor remakeIconsColor[MAX_ICON * ICON_SIZE * ICON_SIZE];
    
    int iconNum;
    int spentFrames;
    bool remakeFlag;
    float doorDeg;
    float downSpeed[MAX_ICON * ICON_SIZE * ICON_SIZE];
    
    void updatePoint();
    void drawDoor(float deg);
    void loadIcon();
    void makeCircle(int w, int h, int x, int y);
    void convergence(int w, int h, int x, int y);
    void remakeCircle(int w, int h, int x, int y);
    void down(int w, int h, int x, int y);
    void remake(int w, int h, int x, int y);
    void nextPhase();
    void loadSpyIcon();
};
#endif