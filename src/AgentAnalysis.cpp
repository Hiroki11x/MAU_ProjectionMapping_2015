//
//  AgentAnalysis.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/07.
//
//
#include "AgentAnalysis.h"

vector<ofVec3f> AgentAnalysis::vertices;

void AgentAnalysis::init(float scale){
 
    ofxAssimpModelLoader model;
    model.loadModel("sphere.stl");
    model.setScale(scale, scale, scale);
    for(int i = 0; i < model.getMeshCount(); i++){
        for(int j = 0; j < 3000; j++){
            vertices.push_back(model.getMesh(i).vertices.at(j) * scale);
        }
    }
}

void AgentAnalysis::drawAgent(){
    ofPushMatrix();
    ofPushStyle();
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofLine(targetPodsition,(position + mesh.vertices.back()).rotated(ofGetElapsedTimeMillis()/100.0 * rotateSpeed,
                                                                     ofGetElapsedTimeMillis()/100.0 * rotateSpeed,
                                                                     ofGetElapsedTimeMillis()/100.0 * rotateSpeed));
    ofRotateX(ofGetElapsedTimeMillis()/100.0 * rotateSpeed);
    ofRotateY(ofGetElapsedTimeMillis()/100.0 * rotateSpeed);
    ofRotateZ(ofGetElapsedTimeMillis()/100.0 * rotateSpeed);

    ofDrawBitmapString("twitter ID ", position * float(vertices.size()) / 3000.0);
    ofDrawBitmapString("Tweeeeeeeeeeeeeeeeeet", position * float(vertices.size()) / 3000.0);

    ofTranslate(position);
    ofSetColor(100, 255, 100,150);
   
    
    /*fontDrawer.drawString("twitter ID and twitter name", 0,0);
    fontDrawer.drawString("Tweeeeeeeeeeeeeeeeeet", 0,-150);*/
    ofSetColor(150,255,100,150);
    mesh.draw(OF_MESH_WIREFRAME);
    ofPopStyle();
    ofPopMatrix();
}

bool AgentAnalysis::removeVertices(){
    if(mesh.vertices.size() == 0){
        return false;
    }
    for(int i = 0; i < 3; i++){
        mesh.vertices.pop_back();
    }
    return true;
}

AgentAnalysis::AgentAnalysis(ofVec3f pos){
    position = pos;
    mesh.addVertices(vertices);
    rotateSpeed = ofRandom(5.0, 20.0);
    fontDrawer.loadFont("Arial.ttf", 20);
}
