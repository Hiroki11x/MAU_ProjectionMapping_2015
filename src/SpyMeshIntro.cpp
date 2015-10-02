//
//  SpyMeshIntro.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/02.
//
//

#include "SpyMeshIntro.h"



void SpyMeshIntro::update(){
    if(isStarted){
        spentFrames+=1;
        for(int i = 0; i < 10; i++){
            targetPoint = garallyModelDrawer.addVertices(spentFrames * 10 + i );
        }
        if(spentFrames % 60 == 0){
            emitPoint = lineEmitPoints[int(ofRandom(0,4))];
        }
        trails.update();
    }
    camera.lookAt(ofPoint(ofGetWidth()/2 + 400, ofGetHeight()/2,70));
    camera.setPosition(ofGetWidth()/2 -ofGetWidth() * 5 * (1.0 - (float)spentFrames * 25.0 / (float)garallyModelDrawer.verticesSize),
                       ofGetHeight() * (1.0 - 0.5 * (float)spentFrames * 25.0 / (float)garallyModelDrawer.verticesSize),
                       70);
}

void SpyMeshIntro::draw(){
    camera.begin();
    
    if(spentFrames > 500){
        ofSetColor(255 * -  (spentFrames - 500), 255, 255 * -  (spentFrames - 500));
        ofDrawSphere(ofPoint(ofGetWidth()/2 + 400, ofGetHeight()/2,70),50 * (spentFrames - 500));
    }
    if(spentFrames > 550 || spentFrames == 0){return;}
    if(spentFrames > 400){
        trails.convergenceMode = true;
    }
    
    ofPushMatrix();
    ofPushStyle();
    trails.drawTrailer();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    ofSetLineWidth(0.3);
    ofSetColor(255, 255, 255 , 150);
    ofRotateX(90);
    garallyModelDrawer.drawModel(0);
    ofLine(emitPoint, targetPoint );
    ofDrawSphere(emitPoint, (60.0 - float(spentFrames % 60)) * 0.8 + 10);
    
    ofPopMatrix();
    ofPopStyle();
    ofDrawBitmapString(ofToString(spentFrames) + " FPS:"+ofToString(ofGetFrameRate()) ,camera.getPosition() + ofPoint(200,0,0));
    camera.end();

}

void SpyMeshIntro::init(){
    
    trails = *new TrailRenderer(ofVec3f(ofGetWidth()/2 -ofGetWidth() * 5 ,ofGetHeight() * 1, 70),
                                ofVec3f(ofGetWidth()/2 + 400, ofGetHeight()/2,70));
    model.loadModel("garally.stl");
    model.setPosition(ofGetWidth()/2, (float)ofGetHeight() * 0.5 , 0);
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.
    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.playAllAnimations();
    spentFrames = 0;
    isStarted = false;
    
    for(int i = 0; i < model.getMeshCount(); i++){
        garallyModelDrawer.setVerices(model.getMesh(i).vertices,200.0);
    }
    lineEmitPointDistance = 100000;
    lineEmitPoints[0] = ofVec3f(lineEmitPointDistance,lineEmitPointDistance,0);
    lineEmitPoints[1] = ofVec3f(- lineEmitPointDistance,lineEmitPointDistance,0);
    lineEmitPoints[2] = ofVec3f(lineEmitPointDistance,- lineEmitPointDistance,0);
    lineEmitPoints[3] = ofVec3f(-lineEmitPointDistance,- lineEmitPointDistance,0);
}
void SpyMeshIntro::onMouseDown(int x, int y){
    isStarted = true;
}