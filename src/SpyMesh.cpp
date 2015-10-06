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
        for(int i = 0; i < ADD_TRIANGLE_PER_UPDATE; i++){
            targetPoint = modelDrawer.addVertex(spentFrames * ADD_TRIANGLE_PER_UPDATE + i );
        }
        if(spentFrames % 60 == 0){
            emitPoint = lineEmitPoints[int(ofRandom(0,4))];
        }
        modelDrawer.changeColoredPartMesh();
        modelDrawer.updateColoredMesh(1.0 + modelSize);
        spentFrames+=1;
    }else{
        wainingFrames++;
    }
    
    float * val = ofSoundGetSpectrum(1);
    modelSize = val[0] * 1;

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
        modelDrawer.drawColoredMesh();
        ofLine(emitPoint, targetPoint);
        sphere.drawSphere(emitPoint, (60.0 - float(spentFrames % 60)) / 60.0 * 0.1 + 0.05);
        ofDrawBitmapString(ofToString(spentFrames) + " FPS:"+ofToString(ofGetFrameRate()) ,emitPoint);
    }
    
    drawEmitter();
    
    ofPopMatrix();
    ofPopStyle();
    
    camera.end();
    
    ofPushStyle();
    ofSetColor(50, 255, 100);
    modelDrawer.drawPercentage();
    ofPopStyle();
}

void SpyMesh::drawEmitter(){

    ofPushStyle();

    ofSetColor(50, 255, 50,150);
    
    for(int i = 0; i < 8; i++){
        ofPushMatrix();
        ofRotateX(ofGetElapsedTimef() * (i + 1) * 20);
        ofRotateY(ofGetElapsedTimef() * (i + 1) * 20);
        ofRotateZ(ofGetElapsedTimef() * (i + 1) * 20);
        if(wainingFrames < 120){
            sphere.drawSphere(lineEmitPoints[i % 4] * float(100 - wainingFrames), 0.15);
        }else{
            sphere.drawSphere(lineEmitPoints[i % 4], 0.1 + 0.5 * modelSize);
        }
        ofPopMatrix();
    }
    ofPopStyle();
}

void SpyMesh::init(){
    
    ofBackground(0);
    soundPlayer.loadSound("mau_music_sample02.aif");
    soundPlayer.setLoop(true);
    soundPlayer.play();
    ofDisableArbTex();
    isStarted = false;
    spentFrames = 0;
    wainingFrames = 0;
    
    initModelDrawer();
    initLineEmitPoints();
}

void SpyMesh::initLineEmitPoints(){
    
    lineEmitPointDistance = 300;
    lineEmitPoints[0] = ofVec3f(lineEmitPointDistance,lineEmitPointDistance,0);
    lineEmitPoints[1] = ofVec3f(- lineEmitPointDistance,lineEmitPointDistance,0);
    lineEmitPoints[2] = ofVec3f(lineEmitPointDistance,- lineEmitPointDistance,0);
    lineEmitPoints[3] = ofVec3f(-lineEmitPointDistance,- lineEmitPointDistance,0);
}

void SpyMesh::initModelDrawer(){
    
    model.clear();
    modelDrawer.setPrimitiveMode(OF_PRIMITIVE_TRIANGLES);
    model.loadModel("MrT3ds/mrt.3ds");
    for(int i = model.getMeshCount() - 1; i > 4; i--){
        modelDrawer.setVertices(model.getMesh(i).vertices, model.getMesh(i).getIndices(), 1.1);
    }
    sphere = *new DrawerSphere(0.15);
}

void SpyMesh::onMouseDown(int x, int y){
    mouseX = x;
    mouseY = y;
    isStarted = true;
}

void SpyMesh::keyPressed(int key){
    switch (key) {
        case 't':
            modelDrawer.setPrimitiveMode(OF_PRIMITIVE_TRIANGLES);
            break;
        case 'l':
            modelDrawer.setPrimitiveMode(OF_PRIMITIVE_LINE_LOOP);
            break;
        case 'p':
            modelDrawer.setPrimitiveMode(OF_PRIMITIVE_POINTS);
            break;
        default:
            break;
    }
}