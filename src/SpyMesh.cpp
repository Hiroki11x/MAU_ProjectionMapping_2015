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
            emitPoint = lineEmitPoints[int(ofRandom(0,6))];
        }
        modelDrawer.changeColoredPartMesh();
        modelDrawer.updateColoredMesh(1.0 + modelSize);
        spentFrames+=1;
    }else{
        wainingFrames++;
    }
    
    float * val = ofSoundGetSpectrum(1);
    modelSize = val[0] * 1;

    camera.setPosition(ofPoint(ofGetWidth()/2 + 300 * sin(float(ofGetElapsedTimef())/3.0) , ofGetHeight()/2 + 300 * cos(float(ofGetElapsedTimef())/3.0) , 150 + 250 * cos(float(ofGetElapsedTimef() / 10.0))));
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
    
    for(int i = 0; i < 6; i++){
        ofPushMatrix();
        ofRotateX(ofGetElapsedTimef() * (i + 1) * 2);
        ofRotateY(ofGetElapsedTimef() * (i + 1) * 2);
        ofRotateZ(ofGetElapsedTimef() * (i + 1) * 2);
        if(wainingFrames < 120){
            sphere.drawSphere(lineEmitPoints[i] * float(100 - wainingFrames), 0.15);
        }else{
            sphere.drawSphere(lineEmitPoints[i], 0.1 + 0.5 * modelSize);
        }
        ofPopMatrix();
    }
    ofPopStyle();
}

void SpyMesh::init(){
    
    ofBackground(0);
    ofDisableArbTex();
    isStarted = false;
    spentFrames = 0;
    wainingFrames = 0;
    SoundManager::init();
    SoundManager::play();
    initModelDrawer();
    initLineEmitPoints();
}

void SpyMesh::initLineEmitPoints(){
    
    lineEmitPointDistance = 600;
    lineEmitPoints[0] = ofVec3f(lineEmitPointDistance,lineEmitPointDistance,0);
    lineEmitPoints[1] = ofVec3f(- lineEmitPointDistance,lineEmitPointDistance,0);
    lineEmitPoints[2] = ofVec3f(lineEmitPointDistance,- lineEmitPointDistance,0);
    lineEmitPoints[3] = ofVec3f(-lineEmitPointDistance,- lineEmitPointDistance,0);
    lineEmitPoints[4] = ofVec3f(0,0,lineEmitPointDistance);
    lineEmitPoints[5] = ofVec3f(0,0,-lineEmitPointDistance);
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
        case 'n':
            modelDrawer.changeColoredMode(ModelDrawer::ColoredMeshMode::LINE);
            break;
        case 'r':
            modelDrawer.changeColoredMode(ModelDrawer::ColoredMeshMode::RANDOM);
            break;
        case 'g':
            modelDrawer.changeColoredMode(ModelDrawer::ColoredMeshMode::AFFECTED_GLAVITY_GLASS);
            break;
        default:
            break;
    }
}