//
//  ArtSpyDeforming.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/09.
//
//
#include "ArtSpyDeforming.h"

void ArtSpyDeforming::init(){
    ofxAssimpModelLoader modelLoader;
    modelLoader.loadModel("logo.stl");
    mesh = modelLoader.getMesh(0);
}

void ArtSpyDeforming::update(){
    rotation +=2.0;
}

void ArtSpyDeforming::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(100, 255, 100);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, -200);
    ofTranslate(0,350,0);
    ofRotateX(90);
    ofRotateZ(rotation);
    light.enable();
    glEnable(GL_LIGHTING);
    mesh.draw();
    light.disable();
    glDisable(GL_LIGHTING);
    ofPopStyle();
    ofPopMatrix();
}