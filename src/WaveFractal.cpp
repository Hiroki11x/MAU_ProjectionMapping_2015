//
//  WaveFractal.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/19.
//
//
#include "WaveFractal.h"

void WaveFractal::init(){
    cam.setPosition(0, 0, 600);
    cam.lookAt(ofPoint(0,0,0));
    reset();
}

void WaveFractal::reset(){
    firstWave = *new Wave(0);
    firstWave.centerPosition = ofVec3f(0,0,0);
}

void WaveFractal::draw(){
    ofSetBackgroundAuto(false);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnableAlphaBlending();
    ofDisableDepthTest();
    ofSetColor(0, 0, 0, 30);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    cam.begin();
    ofPushMatrix();

    ofTranslate(firstWave.centerPosition);
    firstWave.drawWavePoint();
    
    ofPopMatrix();
    cam.end();
}

void WaveFractal::update(){
 

    firstWave.updateWave();
}

//-----------------------------
//Wave Class
//-----------------------------
WaveFractal::Wave::Wave(int gen){
    centerPosition = ofVec3f(ofRandom(-200, 200),ofRandom(-200, 200),ofRandom(-200, 200));
    rotateSpeed = ofRandom(0.1,1.0);
    frequency = ofRandom(100,1000);
    radius = ofRandom(30, 100);
    deg = 0;
    generatedNextWave = false;
    frameCounter = 0;
    nextWaveFrames = ofRandom(60,100);
    generation = gen;
}

void WaveFractal::Wave::drawWavePoint(){
    
    ofTranslate(0,centerPosition.y,0);
    
    
    //if(frameCounter > nextWaveFrames){
        ofNoFill();
        /*ofSetColor(50, 255 * (1.0 - 0.5 * (float)generation/(float)MAX_GENERATION), 255,
                   110 * (1.0 - 0.5 * (float)generation/(float)MAX_GENERATION));*/
    ofSetColor(50, 255 * (1.0 - 0.5 * (float)generation/(float)MAX_GENERATION), 255,
               255);
        ofPushMatrix();
        ofRotateX(90);
        ofCircle(0, 0, frameCounter * 10);
        ofPopMatrix();
        ofFill();
    //}
    
    ofRotateY(deg);
    ofTranslate(radius, 0);
   /* ofSetColor(50, 255,
               255 * (1.0 - 0.5 * (float)generation/(float)MAX_GENERATION),
               255 * (1.0 - 0.5 * (float)generation/(float)MAX_GENERATION));*/
    ofSetColor(50, 255,
               255 * (1.0 - 0.5 * (float)generation/(float)MAX_GENERATION),
               255 );
    ofDrawSphere(0, 0, 5);
    ofRotateZ(90);
    if(!generatedNextWave) return;
    for(int i = 0; i < children.size(); i++){
        ofPushMatrix();
        children.at(i).drawWavePoint();
        ofPopMatrix();
    }
}

void WaveFractal::Wave::updateWave(){
    deg += rotateSpeed;
    
    if(generatedNextWave){
        for(int i = 0; i < children.size(); i++){
            children.at(i).updateWave();
        }
    }else{
        if(generation > MAX_GENERATION) return;
        frameCounter++;
        if(frameCounter > nextWaveFrames){
            generatedNextWave = true;
            //int childnum = 3;
            int childnum = ofRandom(1,MAX_CHILDREN + 1);
            for(int i = 0; i < childnum; i++){
                children.push_back(*new Wave(generation + 1));
            }
        }
    }
}

void WaveFractal::stop(){
    ofSetBackgroundAuto(true);
}
void WaveFractal::onMouseDown(int x, int y){}

void WaveFractal::keyPressed(int key){
    switch (key) {
        case 'R':
            reset();
            break;
        default:
            break;
    }
}