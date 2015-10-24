//
//  ArtSpyDeforming.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/09.
//
//
#ifndef ArtSpyDeforming_h
#define ArtSpyDeforming_h

#include "SceneElement.h"
#include "ofxAssimpModelLoader.h"
#include "CircuitDrawer.h"
#include "FoundationDrawer.h"
#include "ofxRollingCam.h"

class ArtSpyDeforming : public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void keyPressed(int key) override;
    virtual void stop() override;

    bool drawCircuitMode = false;
    bool apperLogo = false;
    float rotation;
    
    vector<float> rotates;
    ofVboMesh mesh;
    ofLight light;
    CircuitDrawer circuitDrawer;
    FoundationDrawer foundationDrawer;
    ofShader backShader;
    
    void drawSpyLogo();
};
#endif