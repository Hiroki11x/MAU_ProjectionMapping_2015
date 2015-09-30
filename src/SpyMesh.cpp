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
    spentFrames++;
}

void SpyMesh::draw(){
    
    ofPushStyle();

    ofSetColor(255);
    ofSetLineWidth(2);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    glShadeModel(GL_SMOOTH); //some model / light stuff
    light.enable();
    ofEnableSeparateSpecularLight();
    
    ofPushMatrix();
    
    ofTranslate(model.getPosition().x+100, model.getPosition().y, 0);
    ofRotate(-spentFrames, 0, 1, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 50 * sin(ofGetElapsedTimeMillis()/240.0));
    model.drawWireframe();
    
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
    //mesh.drawWireframe();
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
    
    ofSetColor(255, 255, 255 );
    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 15);
    ofSetColor(50, 255, 50);
    
    ofPopStyle();
}

void SpyMesh::end(){}

void SpyMesh::init(){
    ofBackground(0);
    model.loadModel("astroBoy_walk.dae");
    model.setPosition(ofGetWidth()/2, (float)ofGetHeight() * 1.0 , 0);
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.
    
    bAnimate = false;
    bAnimateMouse = false;
    animationPosition = 0;
    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.playAllAnimations();
    if(!bAnimate) {
        model.setPausedForAllAnimations(true);
    }
    text = loadText("code.txt");
    spentFrames = 0;
}

void SpyMesh::onMouseDown(int x, int y){
    mouseX = x;
    mouseY = y;
    model.addMesh();
}