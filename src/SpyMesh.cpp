//
//  SpyMesh.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//

#include "SpyMesh.h"

void SpyMesh::update(){
    model.update();
    
    if(bAnimateMouse) {
        model.setPositionForAllAnimations(animationPosition);
    }
    
    mesh = model.getCurrentAnimatedMesh(0);
   
}

void SpyMesh::draw(){
    
    
    
    ofSetColor(255);
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    ofEnableDepthTest();
    
    glShadeModel(GL_SMOOTH); //some model / light stuff
    light.enable();
    ofEnableSeparateSpecularLight();
    
    ofPushMatrix();
    ofTranslate(model.getPosition().x+100, model.getPosition().y, 0);
    ofRotate(-mouseX, 0, 1, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
    model.drawFaces();
    ofPopMatrix();
    
    if(ofGetGLProgrammableRenderer()){
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
    }
    glEnable(GL_NORMALIZE);
    
    ofPushMatrix();
    ofTranslate(model.getPosition().x-300, model.getPosition().y, 0);
    ofRotate(-mouseX, 0, 1, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
    
    ofxAssimpMeshHelper & meshHelper = model.getMeshHelper(0);
    
    ofMultMatrix(model.getModelMatrix());
    ofMultMatrix(meshHelper.matrix);
    
    ofMaterial & material = meshHelper.material;
    if(meshHelper.hasTexture()){
        meshHelper.getTextureRef().bind();
    }
    material.begin();
    mesh.drawWireframe();
    material.end();
    if(meshHelper.hasTexture()){
        meshHelper.getTextureRef().unbind();
    }
    ofPopMatrix();
    
    if(ofGetGLProgrammableRenderer()){
        glPopAttrib();
    }
    
    ofDisableDepthTest();
    light.disable();
    ofDisableLighting();
    ofDisableSeparateSpecularLight();
    
    //ofSetColor(255, 255, 255 );
  /*  ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 15);
    ofDrawBitmapString("keys 1-5 load models, spacebar to trigger animation", 10, 30);
    ofDrawBitmapString("drag to control animation with mouseY", 10, 45);
    ofDrawBitmapString("num animations for this model: " + ofToString(model.getAnimationCount()), 10, 60);*/

 
}

void SpyMesh::end(){}

void SpyMesh::init(){
    ofBackground(0);
    model.loadModel("s.3ds");
    model.setPosition(ofGetWidth()/2, (float)ofGetHeight() * 0.75 , 0);
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.
    
    bAnimate = false;
    bAnimateMouse = false;
    animationPosition = 0;
    
    //model.loadModel("astroBoy_walk.dae", true);
    //model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);
    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.playAllAnimations();
    if(!bAnimate) {
        model.setPausedForAllAnimations(true);
    }
}

void SpyMesh::onMouseDown(int x, int y){
    mouseX = x;
    mouseY = y;
}