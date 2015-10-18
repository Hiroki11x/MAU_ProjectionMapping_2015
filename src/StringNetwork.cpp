//
//  StringNetwork.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/13.
//
//
#include "StringNetwork.h"

void StringNetwork::init(){
    networkAgents = *new vector<NetworkAgent>;
    for(int i = 0; i < MAX_AGENTS; i++){
        networkAgents.push_back(*new NetworkAgent());
    }
    for(int i = 0; i < MAX_AGENTS; i++){
        networkAgents.at(i).position = ofVec2f((i % 8) * 100 , (i / 8) * 100);
        for(int j = 0; j < MAX_AGENTS; j++){
            networkAgents.at(i).NorP.push_back(ofRandom(-0.8,0.9));
        }
    }
    expandingArea = 500;
    cameraZ = 600;
    fontSize = 10;
    font.loadFont("Arial.ttf", fontSize);
    font.loadSubFont("YuMincho");
    font.loadSubFont(OF_TTF_SERIF,1.2,-0.02);
    font.loadSubFont("Geeza Pro",1,-0.04,0x0600,0x06FF,"arab");
    font.useProportional(true);
    font.useVrt2Layout(true);
    font.setLineHeight(font.getFontSize()*1.5);
    agentNum = 0;
    spentFrames = 0;
}

void StringNetwork::update(){
    updateAgents();
    spentFrames++;
    /*cameraRotateFrames++;
    if(cameraRotateFrames < waitFrame){
        if(cameraRotateFrames < rotateFrame){
            cameraPosition += (nextCameraPosition - befCameraPosition) / float(rotateFrame);
            cameraLookPoint += (nextCameraLookPoint - befCameraLookPoint) / float(rotateFrame);
            camera.setPosition(cameraPosition);
            camera.lookAt(cameraLookPoint);
        }
    }else{
        cameraRotateFrames = 0;
        befCameraPosition = cameraPosition;
        nextCameraPosition = ofVec3f(ofRandom(-expandingArea, expandingArea), ofRandom(-expandingArea, expandingArea),ofRandom(-expandingArea, expandingArea));
        befCameraLookPoint = cameraLookPoint;
        nextCameraLookPoint = ofPoint(ofRandom(-(expandingArea - 200),expandingArea - 200), ofRandom(-(expandingArea - 200), expandingArea - 200),ofRandom(-(expandingArea - 200),expandingArea - 200));
        waitFrame = ofRandom(50,100);
        rotateFrame = ofRandom(10,50);
    }*/

  /*  camera.setPosition(-ofGetWidth()/2,-ofGetHeight()/2, -cameraZ);
    camera.lookAt(ofPoint(-ofGetWidth()/2, -ofGetHeight()/2, 0));*/
   // camera.setPosition(0,0, -cameraZ);
   // camera.lookAt(ofPoint(0,0, 0));
    if(!(spentFrames % 10 == 0)) return;
    if(!(agentNum < MAX_AGENTS)) return;
    if(JsonReceiver::getInstance().updateNum <= agentNum) return;
    networkAgents.at(agentNum).validate(JsonReceiver::getInstance().getUserNames().at(agentNum));
    agentNum++;
    
}

void StringNetwork::draw(){

    ofDisableDepthTest();
    ofDisableBlendMode();
    ofDisableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    backShader.load("","shader.frag");
    backShader.begin();
    backShader.setUniform1f("u_time", ofGetElapsedTimef());
    backShader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    ofRect(0,0,ofGetWidth(), ofGetHeight());
    backShader.end();
   
    camera.begin();
    glPushMatrix();
    glRotatef(180, 0, 0, 1);
    ofPushStyle();
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);
   /* light.setPosition(ofGetWidth()/2, ofGetHeight()/2, cameraZ);
    light.lookAt(ofPoint(ofGetWidth()/2, ofGetHeight()/2, 0));*/
    /*light.setPosition(0, 0, cameraZ);
    light.lookAt(ofPoint(0, 0, 0));
    light.enable();
    glEnable(GL_LIGHTING);*/
    for(int i = 0; i < agentNum; i++){
        int lineNum = 0;
        for(int j = i; j < agentNum && lineNum < agentNum/10.0; j++){
            if(networkAgents.at(i).NorP.at(j) < 0) {
                ofSetColor(50, 255, 50, 150);
            }else{
                ofSetColor(100, 255, 255, 150);
            }
           /* ofSetLineWidth(400.0
                           /(networkAgents.at(i).position - networkAgents.at(j).position).length());*/
            ofSetLineWidth(0.3);
            ofLine(networkAgents.at(i).position, networkAgents.at(j).position);
            lineNum++;
        }
    }
    ofSetColor(50, 255, 255 ,210);
    for(int i = 0; i < agentNum; i++){
        glPushMatrix();
        glTranslatef(networkAgents.at(i).position.x, networkAgents.at(i).position.y, networkAgents.at(i).position.z);
        glRotatef(i * 10, 1, 0.1, -0.3);
        font.drawString(networkAgents.at(i).name,0,0,0);
       // networkAgents.at(i).moveToNextPosition();
        glPopMatrix();
    }
    light.disable();
    glDisable(GL_LIGHTING);
    camera.end();
    ofDisableAlphaBlending();
    ofDisableBlendMode();
    ofPopStyle();
    glPopMatrix();
}

void StringNetwork::updateAgents(){
    
    for(int i = 0; i< agentNum; i++){
        if((networkAgents.at(i).nextPosition - networkAgents.at(i).position).length() < 20 || abs(networkAgents.at(i).position.x) > expandingArea ||abs(networkAgents.at(i).position.y) > expandingArea || abs(networkAgents.at(i).position.z) > expandingArea){
            cout << "inti" << i << endl;
            networkAgents.at(i).position = ofVec3f(networkAgents.at(i).nextPosition.x,networkAgents.at(i).nextPosition.y,networkAgents.at(i).nextPosition.z);
            networkAgents.at(i).nextPosition = ofVec3f(ofRandom(-expandingArea,expandingArea),ofRandom(-expandingArea,expandingArea),ofRandom(-expandingArea,expandingArea));
            networkAgents.at(i).befPosition = networkAgents.at(i).position;
            networkAgents.at(i).moveFrame = ofRandom(60,300);
        }else{
          //  cout << spentFrames << ":add:" << i << "diff@" << networkAgents.at(i).difPosition <<endl;
            networkAgents.at(i).position +=  ofVec3f(networkAgents.at(i).nextPosition - networkAgents.at(i).befPosition) / float(networkAgents.at(i).moveFrame);
        }
       /* networkAgents.at(i).nextPosition = networkAgents.at(i).position;
        for(int j = 0; j < agentNum; j++){
            networkAgents.at(i).nextPosition += 0.0020 * networkAgents.at(i).NorP.at(j) * (networkAgents.at(j).position - networkAgents.at(i).position);
        }*/
        /*if(networkAgents.at(i).position.x > ofGetWidth() + expandingArea
           || networkAgents.at(i).position.x < -expandingArea
           || networkAgents.at(i).position.y > ofGetHeight() + expandingArea
           || networkAgents.at(i).position.y < -expandingArea){
            networkAgents.at(i).nextPosition += 0.02 * (ofVec2f(ofGetWidth()/2,ofGetHeight()/2) - networkAgents.at(i).position);
        }else{
            networkAgents.at(i).nextPosition += 0.002 * (ofVec2f(ofGetWidth()/2,ofGetHeight()/2) - networkAgents.at(i).position);
        }*/
       /*  if(networkAgents.at(i).position.x > expandingArea
         || networkAgents.at(i).position.x < -expandingArea
         || networkAgents.at(i).position.y > expandingArea
         || networkAgents.at(i).position.y < -expandingArea){
         networkAgents.at(i).nextPosition += 0.02 * (ofVec3f(0,0,0) - networkAgents.at(i).position);
         }else{
         networkAgents.at(i).nextPosition += 0.002 * (ofVec3f(0,0,0) - networkAgents.at(i).position);
         }*/
    }
}

void StringNetwork::keyPressed(int key){
    switch (key) {
        case 'p':
            cameraZ+=50;
            cout << cameraZ << endl;
            break;
        case 'o':
            expandingArea+=50;
            cout << expandingArea << endl;
            break;
        case 'l':
            cameraZ-=50;
            cout << cameraZ << endl;
            break;
        case 'k':
            if(expandingArea < 50) break;
            expandingArea-=50;
            cout << expandingArea << endl;
            break;
        case 'm':
            fontSize++;
            font.loadFont("Arial.ttf", fontSize);
            font.loadFont("Yumin Demibold",fontSize,true,true,0.3f,0,true)||font.loadSubFont("YuMincho");
            break;
        case 'n':
            fontSize--;
            font.loadFont("Arial.ttf", fontSize);
            font.loadFont("Yumin Demibold",fontSize,true,true,0.3f,0,true)||font.loadSubFont("YuMincho");
            break;
        case 'R':
            init();
        default:
            break;
    }
}
void StringNetwork::onMouseDown(int x, int y){}