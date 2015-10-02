//
//  SpyMesh.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#include "SpyMesh.h"

void SpyMesh::update(){
    
    if(isStarted){
        spentFrames+=1;
        if(spentFrames % 1 == 0){
            targetPoint = modelDrawer.addVertices(spentFrames * 2);
            targetPoint = modelDrawer.addVertices(spentFrames * 2 + 1);
            if(spentFrames % 60 == 0){
                emitPoint = lineEmitPoints[int(ofRandom(0,4))];
            }
        }
    }else{
        wainingFrames++;
    }
    
    float * val = ofSoundGetSpectrum(1);
    modelSize = val[0] * 10;

    camera.setPosition(329 , 131 , 132);
    camera.lookAt(ofPoint(ofGetWidth()/2, ofGetHeight()/2,0));
}

void SpyMesh::draw(){
    
    camera.begin();
    
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofSetColor(50, 255, 50 , 150);
    
    if(isStarted){
        ofSetLineWidth(0.3);
        ofRotateX(ofGetElapsedTimef() * 10);
        ofRotateY(ofGetElapsedTimef() * 10);
        ofRotateZ(ofGetElapsedTimef() * 10);
        modelDrawer.drawModel(modelSize);
        ofLine(emitPoint, targetPoint);
        ofDrawSphere(emitPoint, (60.0 - float(spentFrames % 60)) * 0.8 + 10);
        ofDrawBitmapString(ofToString(spentFrames) + " FPS:"+ofToString(ofGetFrameRate()) ,emitPoint);
    }
    for(int i = 0; i < 8; i++){
        ofPushMatrix();
        ofRotateX(ofGetElapsedTimef() * (i + 1) * 20);
        ofRotateY(ofGetElapsedTimef() * (i + 1) * 20);
        ofRotateZ(ofGetElapsedTimef() * (i + 1) * 20);
        if(wainingFrames < 120){
            ofDrawSphere(lineEmitPoints[i % 4] * float(100 - wainingFrames), (60.0 - float(wainingFrames % 60)) * 0.5);
        }else{
            ofDrawSphere(lineEmitPoints[i % 4], (60.0 - float(spentFrames % 60)) * 0.5);
        }
        ofPopMatrix();
    }
    
    ofPopMatrix();
    ofPopStyle();
    
    camera.end();
}

void SpyMesh::init(){
    
    ofBackground(0);
    soundPlayer.loadSound("star.mp3");
    soundPlayer.play();
    ofDisableArbTex();
    isStarted = false;
    spentFrames = 0;
    wainingFrames = 0;
    model.loadModel("head/TheRock2.obj");
    model.setPosition(ofGetWidth()/2, (float)ofGetHeight() * 0.5 , 0);
    for(int i = 0; i < model.getMeshCount(); i++){
       modelDrawer.setVerices(model.getMesh(i).vertices,1.0);
    }
    lineEmitPointDistance = 200;
    lineEmitPoints[0] = ofVec3f(lineEmitPointDistance,lineEmitPointDistance,0);
    lineEmitPoints[1] = ofVec3f(- lineEmitPointDistance,lineEmitPointDistance,0);
    lineEmitPoints[2] = ofVec3f(lineEmitPointDistance,- lineEmitPointDistance,0);
    lineEmitPoints[3] = ofVec3f(-lineEmitPointDistance,- lineEmitPointDistance,0);
}

void SpyMesh::onMouseDown(int x, int y){
    mouseX = x;
    mouseY = y;
    isStarted = true;
}