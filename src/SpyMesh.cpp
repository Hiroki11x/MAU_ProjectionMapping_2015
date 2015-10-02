//
//  SpyMesh.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#include "SpyMesh.h"

void SpyMesh::update(){
    
    if(button){
        spentFrames+=1;
        if(spentFrames % 1 == 0){
            //Garally
            targetVec = garallyModelDrawer.addVertices(spentFrames * 2 );
            targetVec = garallyModelDrawer.addVertices(spentFrames * 2 + 1);
            
            /* head
            targetVec = modelDrawer.addVertices(spentFrames * 2);
            targetVec = modelDrawer.addVertices(spentFrames * 2 + 1);
             */
            if(spentFrames % 60 == 0){
                fireVec = fromVec[int(ofRandom(0,4))];
            }
        }
    }
    
    float * val = ofSoundGetSpectrum(1);
    modelSize = val[0] * 10;
    
    for(int i = 0; i < 4; i++){
        agents[i].update();
    }

    camera.setPosition(329 , 131 , 132);
    camera.lookAt(ofPoint(ofGetWidth()/2, ofGetHeight()/2,0));
}

void SpyMesh::draw(){
    
    camera.begin();
    
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

    if(button){
        ofSetLineWidth(0.3);
        ofSetColor(50, 255, 50 , 150);
        ofRotateX(ofGetElapsedTimef() * 10);
        ofRotateY(ofGetElapsedTimef() * 10);
        ofRotateZ(ofGetElapsedTimef() * 10);
        //modelDrawer.drawModel(modelSize);
        garallyModelDrawer.drawModel(modelSize); //Garally
        ofLine(fireVec, targetVec );
        ofDrawSphere(fireVec, (60.0 - float(spentFrames % 60)) * 0.8 + 10);
        ofDrawBitmapString(ofToString(spentFrames) + " FPS:"+ofToString(ofGetFrameRate()) ,fireVec);
        for(int i = 0; i < 8; i++){
            ofPushMatrix();
            ofRotateX(ofGetElapsedTimef() * i * 20);
            ofRotateY(ofGetElapsedTimef() * i * 20);
            ofRotateZ(ofGetElapsedTimef() * i * 20);
            ofDrawSphere(fromVec[i % 4], (60.0 - float(spentFrames % 60)) * 0.5);
            ofPopMatrix();
        }
    }
    ofPopMatrix();
    ofPopStyle();
    
    camera.end();
}

void SpyMesh::init(){
    ofBackground(0);
//    soundPlayer.loadSound("star.mp3");
//    soundPlayer.play();
    
    /** 顔
    model.loadModel("head/TheRock2.obj");
    model.setPosition(ofGetWidth()/2, (float)ofGetHeight() * 0.5 , 0);
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

    for(int i = 0; i < model.getMeshCount(); i++){
       modelDrawer.setVerices(model.getMesh(i).vertices,1.0);
    }
    button = false;
     */
    
    
    //Garally
    model.loadModel("garally.stl");
    model.setPosition(ofGetWidth()/2, (float)ofGetHeight() * 0.5 , 0);
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
    
    for(int i = 0; i < model.getMeshCount(); i++){
        garallyModelDrawer.setVerices(model.getMesh(i).vertices,100.0);
    }
    
}

void SpyMesh::onMouseDown(int x, int y){
    mouseX = x;
    mouseY = y;
    button = true;
}