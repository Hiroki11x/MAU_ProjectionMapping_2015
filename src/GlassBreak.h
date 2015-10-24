//
//  GlassBreak.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/21.
//
//
#ifndef GlassBreak_h
#define GlassBreak_h

#include "ofMain.h"
#include "SampleElement.h"
#include "ofxAssimpModelLoader.h"

class GlassBreak : public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    virtual void stop() override;
    void reset();
    ofxAssimpModelLoader glassModel;
    
    ofEasyCam cam;
    ofVboMesh glassMesh;
    vector<ofVec3f> crashSpeeds;
    vector<ofVec3f> crashRotation;
    int glassTriangleNum;
    enum GlassMode{
        DrawGlass,
        DrawedGlass,
        Normal,
        Break
    };
    GlassMode mode;
    ofVboMesh drawingMesh;
    ofVec3f nextVertex;
    ofVec3f befVertex;
    ofVec3f drawingVertex;
    int drawCounter;
    int addedVertex;
    int spentFrames;
};
#endif
