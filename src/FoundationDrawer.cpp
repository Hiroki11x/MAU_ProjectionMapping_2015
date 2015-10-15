//
//  FoundationDrawer.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/15.
//
//

#include "FoundationDrawer.h"

void FoundationDrawer::init(float radius){
    for(int i = 0; i < 3; i++){
        insideCircleMesh.addVertex(ofVec3f( radius * cos(i * 120 / 180.0 * PI), radius * sin(i * 120 / 180.0 * PI), 0));
        for(float deg = 0; deg < 60; deg += 0.5){
            insideCircleMesh.addVertex(ofVec3f(radius * cos((float(i * 120) + deg) / 180.0 * PI),
                                           radius * sin((float(i * 120) + deg) / 180.0 * PI), 0));
            insideCircleMesh.addVertex(ofVec3f(radius * cos((float(i * 120) + deg) / 180.0 * PI),
                                           radius * sin((float(i * 120) + deg) / 180.0 * PI), 0));
        }
        insideCircleMesh.addVertex(ofVec3f(radius * cos((i * 120 + 60) / 180.0 * PI),
                                       radius * sin((i * 120 + 60) / 180.0 * PI), 0));
    }
    insideCircleMesh.setMode(OF_PRIMITIVE_LINES);
    
    for(int i = 0; i < 2; i++){
        middleCircleMesh.addVertex(ofVec3f(radius * (float(i) * 0.2 + MIDDLE_RATE) * cos(0),
                                           radius * (float(i) * 0.2 + MIDDLE_RATE) * sin(0),
                                           0));
        for(float deg = 0; deg < 360; deg += 0.5){
            middleCircleMesh.addVertex(ofVec3f(radius * (float(i) * 0.2 + MIDDLE_RATE) * cos(deg / 180.0 * PI),
                                               radius * (float(i) * 0.2 + MIDDLE_RATE) * sin(deg / 180.0 * PI),
                                               0));
            middleCircleMesh.addVertex(ofVec3f(radius * (float(i) * 0.2 + MIDDLE_RATE) * cos(deg / 180.0 * PI),
                                               radius * (float(i) * 0.2 + MIDDLE_RATE) * sin(deg / 180.0 * PI),
                                               0));
            
        }
        middleCircleMesh.addVertex(ofVec3f(radius * (float(i) * 0.2 + MIDDLE_RATE) * cos(0),
                                           radius  * (float(i) * 0.2 + MIDDLE_RATE) * sin(0),
                                           0));
    }
    
    for(float deg = 0; deg < 360; deg += 10){
        middleCircleMesh.addVertex(ofVec3f(radius * (0.2 + MIDDLE_RATE) * cos(deg / 180.0 * PI),
                                           radius * (0.2 + MIDDLE_RATE) * sin(deg / 180.0 * PI),
                                           0));
        middleCircleMesh.addVertex(ofVec3f(radius * (MIDDLE_RATE) * cos(deg / 180.0 * PI),
                                           radius * (MIDDLE_RATE) * sin(deg / 180.0 * PI),
                                           0));
        
    }
    middleCircleMesh.setMode(OF_PRIMITIVE_LINES);
    
    for(int i = 0; i < 3; i++){
        outsideCircleMesh.addVertex(ofVec3f( radius * OUTSIDE_RATE * cos((i * 120) / 180.0 * PI), radius * OUTSIDE_RATE * sin((i * 120) / 180.0 * PI), 0));
        for(float deg = 0; deg < 90; deg += 0.5){
            outsideCircleMesh.addVertex(ofVec3f(radius * OUTSIDE_RATE * cos((float(i * 120) + deg) / 180.0 * PI),
                                            radius * OUTSIDE_RATE * sin((float(i * 120) + deg) / 180.0 * PI), 0));
            outsideCircleMesh.addVertex(ofVec3f(radius * OUTSIDE_RATE * cos((float(i * 120) + deg) / 180.0 * PI),
                                            radius * OUTSIDE_RATE * sin((float(i * 120) + deg) / 180.0 * PI), 0));
        }
        outsideCircleMesh.addVertex(ofVec3f(radius * OUTSIDE_RATE * cos((i * 120 + 90)/ 180.0 * PI),
                                        radius * OUTSIDE_RATE * sin((i * 120 + 90)/ 180.0 * PI), 0));
    }
    outsideCircleMesh.setMode(OF_PRIMITIVE_LINES);
    
}

void FoundationDrawer::drawFoundation(){
    ofPushMatrix();
    ofPushStyle();
    
    ofNoFill();
    ofPushStyle();
    ofSetColor(0, 255, 255,50);
    for(int h = 0; h < 6; h++){
        ofPushMatrix();
        ofTranslate(0,0, - 4 * h + 10);
        ofCircle(0, 0, 70 - h * 8);
        ofPopMatrix();
    }
    ofPopStyle();
    
    for(int h = 0; h < 2; h++){
        ofTranslate(0,0, - 4 * h);
        
        ofPushMatrix();
        ofSetColor(0, 255, 240,50);
        ofSetLineWidth(10);
        ofRotateZ(insideDeg);
        insideCircleMesh.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofSetColor(0, 255, 240,50);
        ofSetLineWidth(3);
        ofRotateZ(middleDeg);
        middleCircleMesh.drawWireframe();
        ofPopMatrix();
        
        ofPushMatrix();
        ofSetColor(0, 255, 240,50);
        ofSetLineWidth(20);
        ofRotateZ(outsideDeg);
        outsideCircleMesh.draw();
        ofPopMatrix();
    }
    ofPopStyle();
    ofPopMatrix();
}

void FoundationDrawer::update(){
    insideDeg += insideSpeed;
    middleDeg += middleSpeed;
    outsideDeg += outsideSpeed;
}