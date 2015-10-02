//
//  SpyMeshIntro.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/02.
//
//

#include "SpyMeshIntro.h"



void SpyMeshIntro::update(){
    if(start){
        spentFrames+=1;
        if(spentFrames % 1 == 0){
            for(int i = 0; i < 10; i++){
                targetVec = garallyModelDrawer.addVertices(spentFrames * 10 + i );
            }
            if(spentFrames % 60 == 0){
                fireVec = fromVec[int(ofRandom(0,4))];
            }
        }
    }
    camera.lookAt(ofPoint(ofGetWidth()/2 + 400, ofGetHeight()/2,70));
    camera.setPosition(ofGetWidth()/2 -ofGetWidth() * 5 * (1.0 - (float)spentFrames * 25.0 / (float)garallyModelDrawer.verticesSize),
                       ofGetHeight() * (1.0 - 0.5 * (float)spentFrames * 25.0 / (float)garallyModelDrawer.verticesSize),
                       70);
    //cout << spentFrames << endl;//550
    //cout << camera.getPosition() << endl;
}

void SpyMeshIntro::draw(){
    camera.begin();
    
    if(spentFrames > 500){
        ofSetColor(255 * -  (spentFrames - 500), 255, 255 * -  (spentFrames - 500));
        ofDrawBox(ofPoint(ofGetWidth()/2 + 400, ofGetHeight()/2,70),50 * (spentFrames - 500));
        
    }
    /*if(spentFrames > 650){
        manager.nextElement();
        return;
    }*/
    if(spentFrames > 550){
        return;
    }
    
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    if(start){
        ofSetLineWidth(0.3);
        //ofSetColor(50, 255, 50 , 150);
        ofSetColor(255, 255, 255 , 150);
        ofRotateX(90);
        //ofRotateY(ofGetElapsedTimef() * 10);
        //ofRotateZ(ofGetElapsedTimef() * 10);
        garallyModelDrawer.drawModel(0);
        ofLine(fireVec, targetVec );
        ofDrawSphere(fireVec, (60.0 - float(spentFrames % 60)) * 0.8 + 10);
        ofDrawBitmapString(ofToString(spentFrames) + " FPS:"+ofToString(ofGetFrameRate()) ,fireVec);
        /*for(int i = 0; i < 8; i++){
            ofPushMatrix();
            ofRotateX(ofGetElapsedTimef() * i * 20);
            ofRotateY(ofGetElapsedTimef() * i * 20);
            ofRotateZ(ofGetElapsedTimef() * i * 20);
            ofDrawSphere(fromVec[i % 4], (60.0 - float(spentFrames % 60)) * 0.5);
            ofPopMatrix();
        }*/
    }
    ofPopMatrix();
    ofPopStyle();
    
    camera.end();
}

void SpyMeshIntro::init(){
    
    model.loadModel("garally.stl");
    model.setPosition(ofGetWidth()/2, (float)ofGetHeight() * 0.5 , 0);
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.
    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.playAllAnimations();
    spentFrames = 0;
    start = false;
    
    for(int i = 0; i < model.getMeshCount(); i++){
        garallyModelDrawer.setVerices(model.getMesh(i).vertices,200.0);
    }
}
void SpyMeshIntro::onMouseDown(int x, int y){
    start = true;
}