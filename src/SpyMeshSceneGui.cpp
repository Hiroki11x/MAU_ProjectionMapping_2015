//
//  SpyMeshSceneGui.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/16.
//
//
#include "SpyMeshSceneGui.h"

void SpyMeshSceneGui::init(){
    font = new ofxTrueTypeFontUL2();
    font->loadFont("Arial.ttf", 20);
    font->loadSubFont("YuMincho");
    font->loadSubFont(OF_TTF_SERIF,1.2,-0.02);
    font->loadSubFont("Geeza Pro",1,-0.04,0x0600,0x06FF,"arab");
    font->useProportional(true);
    font->useVrt2Layout(true);
    font->setLineHeight(font->getFontSize()*1.5);
    nameFont = new ofxTrueTypeFontUL2();
    nameFont->loadFont("Arial.ttf", 10);
    nameFont->loadSubFont("YuMincho");
    nameFont->loadSubFont(OF_TTF_SERIF,1.2,-0.02);
    nameFont->loadSubFont("Geeza Pro",1,-0.04,0x0600,0x06FF,"arab");
    nameFont->useProportional(true);
    nameFont->useVrt2Layout(true);
    nameFont->setLineHeight(nameFont->getFontSize()*1.5);
    befAgentNum = 0;
    initFoundation();
}

void SpyMeshSceneGui::drawGui(vector<AgentAnalysis> agents){
    ofPushMatrix();
    ofPushStyle();
    
    drawBackLine();
    drawEntry(agents);
    
    ofDisableDepthTest();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2 + 300);
    ofRotateX(120);
    drawFoundation();
    ofPopMatrix();
    ofPopStyle();
}

void SpyMeshSceneGui::updateGui(){
    insideDeg += insideSpeed;
    middleDeg += middleSpeed;
    outsideDeg += outsideSpeed;
    for(int i = 0; i < newAgentWaves.size(); i++){
        newAgentWaves.at(i).size += ofRandom(1.0, 10.0);
        if(newAgentWaves.at(i).size > 1500){
            newAgentWaves.erase(newAgentWaves.begin() + i);
            i--;
        }
    }
}


void SpyMeshSceneGui::drawEntry(vector<AgentAnalysis> agents){
    ofPushMatrix();
    drawAnalyzer();
    ofTranslate(0, 50);
    
    ofSetColor(80,120,80,100);
    ofRect(40, 90 , 220 , 40 + 30 * agents.size());
    ofNoFill();
    ofSetColor(200, 255, 200,80);
    ofRect(50, 100 , 200 , 20 + 30 * agents.size());
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(50, 100 + 10);
    ofFill();
    for(int i = 0; i < agents.size(); i++){
        ofPushMatrix();
        if(i >= befAgentNum){
            newAgentWaves.push_back((newAgentWave){0,i,(int)ofRandom(0.9),ofRandom(90.0)});
        }
        ofTranslate(0, 30 * i);
        ofSetColor(80, 230, 80, 150);
        ofRect(5, 5, 190.0 * (float)agents.at(i).mesh.vertices.size() / 3000.0, 20);
        ofSetColor(210, 255, 210,220);
        nameFont->drawString(agents.at(i).userName, 10, 20);
        ofPopMatrix();
    }
    ofNoFill();
    ofSetColor(100, 255, 100,100);
    for(int i = 0; i < newAgentWaves.size(); i++){
        ofPushMatrix();
        ofTranslate(-newAgentWaves.at(i).size / 10.0, 30 * newAgentWaves.at(i).index - newAgentWaves.at(i).size / 2.0);
       // ofRotateZ(newAgentWaves.at(i).rotation);
        switch (newAgentWaves.at(i).shapeType) {
            case 0:
                ofRect(0, 0, newAgentWaves.at(i).size * 3.0, newAgentWaves.at(i).size);
                break;
            case 1:
                ofEllipse(0, 0, newAgentWaves.at(i).size * 3.0 , newAgentWaves.at(i).size);
                break;
            case 2:
                ofTriangle(0, 0, newAgentWaves.at(i).size * 3.0, -newAgentWaves.at(i).size, newAgentWaves.at(i).size * 3.0, newAgentWaves.at(i).size);
            default:
                break;
        }
        ofPopMatrix();
    }
    ofPopMatrix();
    ofPopStyle();
    ofFill();
    befAgentNum = agents.size();
    
    ofPopMatrix();
}

void SpyMeshSceneGui::drawAnalyzer(){
    ofSetColor(255, 255, 255, 100);
    ofLine(40, 115, 220, 115);
    ofLine(220, 115, 260, 115);
    ofSetColor(100, 255, 100, 150);
    font->drawString("Analyst", 100, 120);
}

void SpyMeshSceneGui::drawBackLine(){
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x000F);
    ofSetColor(10, 255, 255, 60);
    for(int w = 0; w < ofGetWidth(); w+= 90){
        ofLine(w , 0, w, ofGetHeight());
    }
    for(int h = 0; h < ofGetHeight(); h += 90){
        ofLine(0, h , ofGetWidth(), h);
    }
    glDisable(GL_LINE_STIPPLE);
}

void SpyMeshSceneGui::drawFoundation(){
    ofPushMatrix();
    ofPushStyle();
    
    ofNoFill();
    /*ofPushStyle();
    ofSetColor(0, 255, 255,50);
    for(int h = 0; h < 6; h++){
        ofPushMatrix();
        ofTranslate(0,0, - 4 * h + 10);
        ofCircle(0, 0, 70 - h * 8);
        ofPopMatrix();
    }
    ofPopStyle();*/
    
    for(int h = 0; h < 2; h++){
        ofTranslate(0,0, - 4 * h);
        
        ofPushMatrix();
        ofSetColor(70, 255, 70,50);
        ofSetLineWidth(10);
        ofRotateZ(insideDeg);
        insideCircleMesh.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        ofSetColor(60, 245, 60,50);
        ofSetLineWidth(3);
        ofRotateZ(middleDeg);
        middleCircleMesh.drawWireframe();
        ofPopMatrix();
        
        ofPushMatrix();
        ofSetColor(100, 255, 100,50);
        ofSetLineWidth(20);
        ofRotateZ(outsideDeg);
        outsideCircleMesh.draw();
        ofPopMatrix();
    }
    ofPopStyle();
    ofPopMatrix();

}

void SpyMeshSceneGui::initFoundation(){
    float radius = 50.0;
    for(int n = 0; n < 4; n++){
        radius = 50.0 + n * 50.0;
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
    }
    insideCircleMesh.setMode(OF_PRIMITIVE_LINES);
    radius = 200.0;
    
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


