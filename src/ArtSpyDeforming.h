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
//#include "ofxFfd.h"
#include "ofxAssimpModelLoader.h"

class ArtSpyDeforming : public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    //virtual void onMouseDown(int x,int y) override;
   // virtual void keyPressed(int key) override;
    
   // ofxFfd ffd;
    ofVboMesh mesh;
    vector<float> rotates;
    ofLight light;
    float rotation;
};
#endif
