//
//  UtVj.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#include "UtVj.h"


void UtVj::reset(){
    offset -= 150*MAX;
}

//--------------------------------------------------------------
void UtVj::setup(){

}

//--------------------------------------------------------------
void UtVj::update(){
    term = (float)ofGetFrameNum()/2*ofGetElapsedTimef() + offset;
    if(term>150*MAX){
        reset();
    }else{
        cam.setPosition(0,0, term);
    }
    cam.lookAt(ofVec3f(0,0,500+term));
}

//--------------------------------------------------------------
void UtVj::draw(){
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofNoFill();
    ofSetLineWidth(2.5);
    cam.begin();
    for(float i=term/150;i<MAX;i+=1){
        ofSetColor(ofColor::fromHsb((int)(i*2)%256, 255, 255),230);
        ofDrawBox(0,0,i*150,100+100*((int)i%5));
        ofRotate(-(i/40)-(float)ofGetElapsedTimef()/500);
    }
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    ofPopMatrix();
    cam.end();
    
    ofFill();
}

void UtVj::keyPressed(int key){
    
}
