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
    font->loadFont("Fonts/Gidole-Regular.ttf",30,true,true,0.3f,0,true);
    font->loadSubFont("Fonts/KozGoPro-Light.otf");
    font->loadSubFont("Fonts/Futura.ttc");
    font->loadSubFont("Fonts/FiraCode-Regular.otf");
    font->useProportional(true);
    font->useVrt2Layout(true);
    font->setLineHeight(font->getFontSize()*1.5);
    nameFont = new ofxTrueTypeFontUL2();
    nameFont->loadFont("Fonts/Gidole-Regular.ttf",20,true,true,0.3f,0,true);
    nameFont->loadSubFont("Fonts/KozGoPro-Bold.otf");
    nameFont->loadSubFont("Fonts/Futura.ttc");
    nameFont->loadSubFont("Fonts/FiraCode-Regular.otf");
    nameFont->useProportional(true);
    nameFont->useVrt2Layout(true);
    nameFont->setLineHeight(nameFont->getFontSize()*1.5);
    befAgentNum = 0;
    initFoundation();
    DNAmodel.loadModel("DNA2.obj");
    DNAmodel.setScale(0.95, 0.95, 0.95);
    waves = vector<Wave>(MAX_WAVE);
}

void SpyMeshSceneGui::drawGui(vector<AgentAnalysis> agents){
    ofPushMatrix();
    ofPushStyle();
    drawBackLine();
    drawEntry(agents);
    drawFoundation();
    if(drawWaveMode) drawWave();
    if(drawTargetLineMode) drawTargetLine();
    if(drawDNAmode) drawDNA();
    ofPopMatrix();
    ofPopStyle();
}

void SpyMeshSceneGui::updateGui(){
    //----------------------------------------------------------
    //AgentEntry
    //----------------------------------------------------------
    for(int i = 0; i < newAgentWaves.size(); i++){
        newAgentWaves.at(i).size += ofRandom(1.0, 10.0);
        if(newAgentWaves.at(i).size > 1500){
            newAgentWaves.erase(newAgentWaves.begin() + i);
            i--;
        }
    }

    //----------------------------------------------------------
    //DNA
    //----------------------------------------------------------
    if(drawDNAmode){
        if(dnaWindowHeight < 700) dnaWindowHeight += 50;
    }else{
        dnaWindowHeight = 20;
    }
    
    //----------------------------------------------------------
    //Found
    //----------------------------------------------------------
    insideDeg += insideSpeed;
    middleDeg += middleSpeed;
    outsideDeg += outsideSpeed;
    
    //----------------------------------------------------------
    //TargetLine
    //----------------------------------------------------------
    if((nextPosition - position).length() < 10){
        if(targetWaitFrame > 100){
            nextPosition = ofVec2f(ofRandom(300, ofGetWidth() - 300),
                                   ofRandom(200, ofGetHeight() - 100));
            difPosition = (nextPosition - position) / float(int(ofRandom(60, 100)));
            targetWaitFrame = 0;
            targetMoving = true;
        }else{
            targetWaitFrame += ofRandom(0.7,2.0);
            targetMoving = false;
            targetCircleSize = ofRandom(0,300);
        }
    }else{
        position += difPosition;
    }
    
    //----------------------------------------------------------
    //Wave
    //----------------------------------------------------------
    if(drawWaveMode){
        if(waveWindowHeight < 20 + 120 * waveNum){
            waveWindowHeight += 60;
        }
        if(waveWindowHeight > 20 + 120 * waveNum){
            waveWindowHeight -= 60;
        }
        if(waveWindowHeight >= 20 + 120 * waveNum - 5 && waveWindowHeight <= 20 + 120 * waveNum + 5){
            waveWindowHeight = 20 + 120 * waveNum;
        }
    }else{
        waveWindowHeight = 20;
    }
    updateWave();
}

void SpyMeshSceneGui::drawBackLine(){
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x000F);
    ofSetColor(10, 255, 255, 60);
    ofSetColor(10, 255, 255, 255);
    for(int w = 0; w < ofGetWidth(); w+= 90){
        ofLine(w , 0, w, ofGetHeight());
    }
    for(int h = 0; h < ofGetHeight(); h += 90){
        ofLine(0, h , ofGetWidth(), h);
    }
    glDisable(GL_LINE_STIPPLE);
}

//----------------------------------------------------------
//AgentEntry
//----------------------------------------------------------
void SpyMeshSceneGui::drawEntry(vector<AgentAnalysis> agents){
    drawAnalyzer();
   
    ofPushMatrix();
    
    ofTranslate(0, 50);
    
    ofSetColor(agentEntryFrameColor);
   // ofRect(40, 90 , 220 , 40 + 30 * agents.size());
     ofRect(40, 90 , 280 , 40 + 50 * agents.size());
    ofSetColor(agentEntryBackColor);
   // ofRect(50, 100 , 200 , 20 + 30 * agents.size());
    ofRect(50, 100 , 260 , 20 + 50 * agents.size());
    
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(50, 100 + 10);
    ofFill();
    
    for(int i = 0; i < agents.size(); i++){
        
        ofPushMatrix();
        
        if(i >= befAgentNum){
            newAgentWaves.push_back((newAgentWave){0,i,(int)ofRandom(0.9),ofRandom(90.0)});
        }
        //ofTranslate(0, 30 * i);
        ofTranslate(0, 50 * i);
        ofSetColor(agentBarColor);
        //ofRect(5, 5, 190.0 * (float)agents.at(i).mesh.vertices.size() / 3000.0, 20);
        ofRect(5, 5, 250.0 * (float)agents.at(i).mesh.vertices.size() / 3000.0, 40);
        ofSetColor(agentNameColor);
        nameFont->drawString(agents.at(i).userName, 10, 33);
        
        ofPopMatrix();
    }
    
    ofNoFill();
    ofSetColor(agentEntryNewWaveColor);
    for(int i = 0; i < newAgentWaves.size(); i++){
        
        ofPushMatrix();
        
        ofTranslate(-newAgentWaves.at(i).size / 10.0, 30 * newAgentWaves.at(i).index - newAgentWaves.at(i).size / 2.0);
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
    ofSetColor(agentAnalistLineColor);
    ofLine(40, 115, 220, 115);
    ofLine(220, 115, 320, 115);
    ofSetColor(agentAnalistColor);
    font->drawString("Analyst", 100, 125);
}

//----------------------------------------------------------
//DNA
//----------------------------------------------------------
void SpyMeshSceneGui::drawDNA(){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(ofGetWidth() - 190, 150);
    ofSetColor(dnaFrameColor);
    ofFill();
    //ofRect(0, 0, 150 , dnaWindowHeight);
    ofRect(-30, 0, 200 , dnaWindowHeight);
    ofSetColor(dnaBackColor);
    ofRect(-20, 10, 180 , dnaWindowHeight - 20);
    //ofTranslate(65, 130);
    ofTranslate(65, 360);
    ofRotateY(ofGetElapsedTimeMillis()/10.0);
    ofSetColor(dnaModelColor);
    if(dnaWindowHeight >= 500) DNAmodel.drawWireframe();
    ofPopMatrix();
    ofPopStyle();
}

//----------------------------------------------------------
//TargetLine
//----------------------------------------------------------
void SpyMeshSceneGui::drawTargetLine(){
    ofPushStyle();
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1 , 0x000F);
    ofSetColor(targetColor);
    ofNoFill();
    if(!targetMoving) ofCircle(position, targetCircleSize);
    ofLine(0, position.y, ofGetWidth(), position.y);
    ofLine(position.x , 0 , position.x , ofGetHeight());
    glDisable(GL_LINE_STIPPLE);
    ofPopStyle();
}

//----------------------------------------------------------
//Wave
//----------------------------------------------------------
void SpyMeshSceneGui::updateWave(){
    for(int i = 0; i < waveNum; i++){
        waves.at(i).intervalCounter++;
        if(waves.at(i).intervalCounter > waves.at(i).nextInterval){
            waves.at(i).waveMesh.addVertex(ofVec2f(0,ofRandom(-40,40)));
            waves.at(i).intervalCounter = 0;
            waves.at(i).nextInterval = ofRandom(10);
            
        }
        float dif = ofRandom(1.5);
        for(int n = 0; n < waves.at(i).waveMesh.vertices.size(); n++){
            waves.at(i).waveMesh.vertices.at(n).x += dif;
            if(waves.at(i).waveMesh.vertices.at(n).x > 280){
                waves.at(i).waveMesh.vertices.erase(waves.at(i).waveMesh.vertices.begin() + n);
                n--;
            }
        }
    }
}

void SpyMeshSceneGui::drawWave(){
    ofPushMatrix();
    //ofTranslate(ofGetWidth() - 240, 100);
    ofTranslate(ofGetWidth() - 340, 100);
    ofSetColor(waveFrameColor);
    ofFill();
    //ofRect(0, 0, 200 , waveWindowHeight);
    ofRect(0, 0, 300 , waveWindowHeight);
    ofTranslate(10, 10);
    for(int i = 0 ; i < waveNum; i++){
        ofPushMatrix();
        
        ofTranslate(0, i * 120);
        ofSetColor(waveBackColor);
        ofFill();
        //ofRect(0, 5, 180,90);
        ofRect(0, 5, 280,110);
        ofNoFill();
        
        ofTranslate(0,50);
        if(waveWindowHeight < 20 + 120 * (i + 1)){
            ofPopMatrix();
            break;
        }
        ofSetColor(waveColor);
        waves.at(i).waveMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
        waves.at(i).waveMesh.draw();
        glPointSize(4);
        waves.at(i).waveMesh.setMode(OF_PRIMITIVE_POINTS);
        waves.at(i).waveMesh.draw();
        
        ofPopMatrix();
    }
    ofPopMatrix();
}

void SpyMeshSceneGui::addWave(){
    if(waveNum < 5) waveNum++;
}

void SpyMeshSceneGui::eraseWave(){
     if(waveNum > 1) waveNum--;
}

//----------------------------------------------------------
//Found
//----------------------------------------------------------
void SpyMeshSceneGui::drawFoundation(){
    ofDisableDepthTest();
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2 + 350);
    ofRotateX(120);
    
    ofNoFill();
    
    for(int h = 0; h < 2; h++){
        ofTranslate(0,0, - 4 * h);
        
        ofPushMatrix();
        ofSetColor(foundInsideColor);
        ofSetLineWidth(10);
        ofRotateZ(insideDeg);
        insideCircleMesh.draw();
        ofPopMatrix();
        
        ofPushMatrix();
        
        ofSetColor(foundMiddleColor);
        ofSetLineWidth(3);
        ofRotateZ(middleDeg);
        middleCircleMesh.drawWireframe();
        ofPopMatrix();
        
        ofPushMatrix();
        ofSetColor(foundOutsideColor);
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


