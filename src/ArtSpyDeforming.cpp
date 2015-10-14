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
    light.setDirectional();
    light.setAmbientColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));//環境反射光の色
    light.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0));//拡散反射光の色
    light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));//鏡面反射光の色
    circuitDrawer = *new CircuitDrawer();
    circuitDrawer.init();
}

void ArtSpyDeforming::update(){
    rotation +=2.0;
    circuitDrawer.updateCircuite();
}

void ArtSpyDeforming::draw(){
    backShader.load("","shader.frag");
    backShader.begin();
    backShader.setUniform1f("u_time", ofGetElapsedTimef());
    backShader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    ofRect(0,0,ofGetWidth(), ofGetHeight());
    backShader.end();
    
    ofEnableAlphaBlending();
    ofDisableDepthTest();
    circuitDrawer.drawCircuit();
    ofDisableBlendMode();
    ofDisableAlphaBlending();
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(40, 255, 40);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, -200);
    ofTranslate(0,300,0);
    ofRotateX(90);
    ofRotateZ(rotation);
    ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
    light.enable();
    glEnable(GL_LIGHTING);
    mesh.draw();
    light.disable();
    glDisable(GL_LIGHTING);
    ofPopStyle();
    ofPopMatrix();
    ofPushStyle();
    ofSetColor(0);
    ofPopStyle();
}