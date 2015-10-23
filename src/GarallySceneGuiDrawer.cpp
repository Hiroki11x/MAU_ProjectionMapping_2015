//
//  GarallySceneGuiDrawer.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/15.
//
//
#include "GarallySceneGuiDrawer.h"

void GarallySceneGuiDrawer::init(){
    frameCounter = 0;
    initFrame();
    initCenterCircle();
    graph = *new GraphGuiDrawer();
    marker = *new TargetMarkerDrawer();
    marker.init(50);
    font.loadFont("Fonts/Gidole-Regular.ttf", 10);
}

void GarallySceneGuiDrawer::update(){
    if(drawGraphMode) graph.updateGraphParams();
    if(drawTargetMarkerMode) marker.update();
    if(drawCenterCircleMode) centerDeg += 0.2;
    if(drawClockMode){
        for(int i = 0; i < 3; i++){
            clockDeg[i] += ofRandom(0, (i + 1) * 10);
        }
    }
    frameCounter++;
}

void GarallySceneGuiDrawer::drawGui(){
    ofPushMatrix();
    ofPushStyle();
    if(drawClockMode) drawClock();
    if(drawTargetMarkerMode) marker.drawTargetMarker(targetColor);
    ofSetColor(frameMeshColor);
    ofSetLineWidth(3);
    frameMesh.draw();

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x000F);
    ofSetColor(backCrossColor);
    for(int w = 0; w < ofGetWidth(); w+= 120){
        ofLine(w , 0, w, ofGetHeight());
    }
    for(int h = 0; h < ofGetHeight(); h += 120){
        ofLine(0, h , ofGetWidth(), h);
    }
    glDisable(GL_LINE_STIPPLE);
    
    if(drawCenterCircleMode){
        ofPushStyle();
        ofPushMatrix();
        ofSetCircleResolution(30);
        ofNoFill();
        ofSetColor(centerCircleColor);
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofSetLineWidth(2);
        ofCircle(0, 0, 230);
        ofLine(-260,0,-200,0);
        ofLine(260,0,200,0);
        ofLine(0,260,0,200);
        ofLine(0,-260,0,-200);
        ofRotateZ(centerDeg);
        ofSetLineWidth(6);
        centerCircle.draw();
        ofPopMatrix();
        ofPopStyle();
    }
    if(drawGraphMode){
        //ofTranslate(80, 580);
        ofTranslate(80, ofGetHeight() - 200);
        graph.drawGraphGui(graphBackColor, graphStringColor, graphBarColor);
    }
    ofPopStyle();
    ofPopMatrix();
}

void GarallySceneGuiDrawer::drawClock(){
    ofPushMatrix();
    ofPushStyle();
    //ofTranslate(830,70);
    ofTranslate(ofGetWidth() - 200,70);
    ofSetColor(clockBackColor);
    ofNoFill();
    ofSetLineWidth(5);
    ofSetColor(clockFrameColor);
    ofRect(0, 0, 100, 280);
    ofTranslate(50, 50);
    for(int i = 0; i < 3; i++){
        ofPushMatrix();
        ofTranslate(0, i * 90);
        ofSetColor(clockDegColor);
        font.drawString(ofToString(i + 1) + ofToString(clockDeg[i]), -30, -33);
        ofSetLineWidth(2);
        ofSetColor(clockCircleColor);
        ofCircle(0, 0, 25);
        ofRotateZ(clockDeg[i]);
        ofSetColor(clockLineColor);
        ofSetLineWidth(3);
        ofLine(0, 0, 30, 0);
        ofPopMatrix();
    }
    ofPopMatrix();
    ofPopStyle();
}

void GarallySceneGuiDrawer::initCenterCircle(){
    float radius = 225.0;
    for(int i = 0; i < 3; i++){
        centerCircle.addVertex(ofVec3f( radius * cos(i * 120 / 180.0 * PI), radius * sin(i * 120 / 180.0 * PI), 0));
        for(float deg = 0; deg < 60; deg += 0.5){
            centerCircle.addVertex(ofVec3f(radius * cos((float(i * 120) + deg) / 180.0 * PI),
                                           radius * sin((float(i * 120) + deg) / 180.0 * PI), 0));
            centerCircle.addVertex(ofVec3f(radius * cos((float(i * 120) + deg) / 180.0 * PI),
                                           radius * sin((float(i * 120) + deg) / 180.0 * PI), 0));
        }
        centerCircle.addVertex(ofVec3f(radius * cos((i * 120 + 60) / 180.0 * PI),
                                       radius * sin((i * 120 + 60) / 180.0 * PI), 0));
    }
    centerCircle.setMode(OF_PRIMITIVE_LINES);
}

void GarallySceneGuiDrawer::initFrame(){
    //leftSide
    /*frameMesh.addVertex(ofVec3f(70,34,0));
    frameMesh.addVertex(ofVec3f(70,234,0));
    frameMesh.addVertex(ofVec3f(70,234,0));
    frameMesh.addVertex(ofVec3f(45,334,0));
    frameMesh.addVertex(ofVec3f(45,334,0));
    frameMesh.addVertex(ofVec3f(45,434,0));
    frameMesh.addVertex(ofVec3f(45,434,0));
    frameMesh.addVertex(ofVec3f(70,534,0));
    frameMesh.addVertex(ofVec3f(70,534,0));
    frameMesh.addVertex(ofVec3f(70,734,0));*/
    frameMesh.addVertex(ofVec3f(70,34,0));
    frameMesh.addVertex(ofVec3f(70,334,0));
    frameMesh.addVertex(ofVec3f(70,334,0));
    frameMesh.addVertex(ofVec3f(45,434,0));
    frameMesh.addVertex(ofVec3f(45,434,0));
    frameMesh.addVertex(ofVec3f(45,534,0));
    frameMesh.addVertex(ofVec3f(45,534,0));
    frameMesh.addVertex(ofVec3f(70,634,0));
    frameMesh.addVertex(ofVec3f(70,634,0));
    frameMesh.addVertex(ofVec3f(70,ofGetHeight() - 50,0));
    //bottom
   /* frameMesh.addVertex(ofVec3f(70,734,0));
    frameMesh.addVertex(ofVec3f(191,734,0));
    frameMesh.addVertex(ofVec3f(191,734,0));
    frameMesh.addVertex(ofVec3f(312,704,0));
    frameMesh.addVertex(ofVec3f(312,704,0));
    frameMesh.addVertex(ofVec3f(712,704,0));
    frameMesh.addVertex(ofVec3f(712,704,0));
    frameMesh.addVertex(ofVec3f(833,734,0));
    frameMesh.addVertex(ofVec3f(833,734,0));
    frameMesh.addVertex(ofVec3f(ofGetWidth() - 70,734,0));*/
    
     frameMesh.addVertex(ofVec3f(70,ofGetHeight() - 50,0));
     frameMesh.addVertex(ofVec3f(391,ofGetHeight() - 50,0));
     frameMesh.addVertex(ofVec3f(391,ofGetHeight() - 50,0));
     frameMesh.addVertex(ofVec3f(512,ofGetHeight() - 80,0));
     frameMesh.addVertex(ofVec3f(512,ofGetHeight() - 80,0));
     frameMesh.addVertex(ofVec3f(912,ofGetHeight() - 80,0));
     frameMesh.addVertex(ofVec3f(912,ofGetHeight() - 80,0));
     frameMesh.addVertex(ofVec3f(1033,ofGetHeight() - 50,0));
     frameMesh.addVertex(ofVec3f(1033,ofGetHeight() - 50,0));
     frameMesh.addVertex(ofVec3f(ofGetWidth() - 70,ofGetHeight() - 50,0));
    //rightSide
    /*frameMesh.addVertex(ofVec3f(954,734,0));
    frameMesh.addVertex(ofVec3f(954,534,0));
    frameMesh.addVertex(ofVec3f(954,534,0));
    frameMesh.addVertex(ofVec3f(989,434,0));
    frameMesh.addVertex(ofVec3f(989,434,0));
    frameMesh.addVertex(ofVec3f(989,334,0));
    frameMesh.addVertex(ofVec3f(989,334,0));
    frameMesh.addVertex(ofVec3f(954,234,0));
    frameMesh.addVertex(ofVec3f(954,234,0));
    frameMesh.addVertex(ofVec3f(954,34,0));*/
    frameMesh.addVertex(ofVec3f(ofGetWidth() - 70,ofGetHeight() - 50,0));
    frameMesh.addVertex(ofVec3f(ofGetWidth() - 70,634,0));
    frameMesh.addVertex(ofVec3f(ofGetWidth() - 70,634,0));
    frameMesh.addVertex(ofVec3f(ofGetWidth() - 35,534,0));
    frameMesh.addVertex(ofVec3f(ofGetWidth() - 35,534,0));
    frameMesh.addVertex(ofVec3f(ofGetWidth() - 35,434,0));
    frameMesh.addVertex(ofVec3f(ofGetWidth() - 35,434,0));
    frameMesh.addVertex(ofVec3f(ofGetWidth() - 70,334,0));
    frameMesh.addVertex(ofVec3f(ofGetWidth() - 70,334,0));
    frameMesh.addVertex(ofVec3f(ofGetWidth() - 70,34,0));
    //top
    frameMesh.addVertex(ofVec3f(ofGetWidth() - 70,34,0));
    frameMesh.addVertex(ofVec3f(1033,34,0));
    frameMesh.addVertex(ofVec3f(1033,34,0));
    frameMesh.addVertex(ofVec3f(912,64,0));
    frameMesh.addVertex(ofVec3f(912,64,0));
    frameMesh.addVertex(ofVec3f(512,64,0));
    frameMesh.addVertex(ofVec3f(512,64,0));
    frameMesh.addVertex(ofVec3f(391,34,0));
    frameMesh.addVertex(ofVec3f(391,34,0));
    frameMesh.addVertex(ofVec3f(70,34,0));
  
    frameMesh.setMode(OF_PRIMITIVE_LINES);
}