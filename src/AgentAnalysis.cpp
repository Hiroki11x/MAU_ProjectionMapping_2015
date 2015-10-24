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
    if(mesh.vertices.size() == 0) return;
    ofSetLineWidth(3);
    ofLine(targetPodsition,(position + mesh.vertices.back()).rotated(ofGetElapsedTimeMillis()/100.0 * rotateSpeed,
                                                                     ofGetElapsedTimeMillis()/100.0 * rotateSpeed,
                                                                     ofGetElapsedTimeMillis()/100.0 * rotateSpeed));
    /*ofSetColor(100, 255, 100,150);
    glPushMatrix();
    glTranslatef(position.x,
                 position.y,
                 position.z);
    font->drawString(userName,0,0);
    glPopMatrix();*/
    ofRotateX(ofGetElapsedTimeMillis()/100.0 * rotateSpeed);
    ofRotateY(ofGetElapsedTimeMillis()/100.0 * rotateSpeed);
    ofRotateZ(ofGetElapsedTimeMillis()/100.0 * rotateSpeed);
    ofTranslate(position);
    //ofSetColor(150,255,100,150);
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

AgentAnalysis::AgentAnalysis(ofVec3f pos, wstring name){
  //  font = new ofxTrueTypeFontUL2();
    position = pos;
    mesh.addVertices(vertices);
    rotateSpeed = ofRandom(2.0, 10.0);
 /*   font->loadFont("Arial.ttf", 10);
    font->loadSubFont("YuMincho");
    font->loadSubFont(OF_TTF_SERIF,1.2,-0.02);
    font->loadSubFont("Geeza Pro",1,-0.04,0x0600,0x06FF,"arab");
    font->useProportional(true);
    font->useVrt2Layout(true);
    font->setLineHeight(font->getFontSize()*1.5);*/
    userName = name;
    eraseSpeed = ofRandom(0.03,0.1);
}
