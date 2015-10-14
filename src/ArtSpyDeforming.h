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

class ArtSpyDeforming : public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void keyPressed(int key) override;
    
    vector<float> rotates;
    ofVboMesh mesh;
    ofLight light;
    CircuitDrawer circuitDrawer;
    ofShader backShader;
    float rotation;
    bool drawCircuitMode = false;
};
#endif