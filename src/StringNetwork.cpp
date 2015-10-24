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
    font.loadFont("Fonts/Gidole-Regular.ttf",10,true,true,0.3f,0,true);
    font.loadSubFont("Fonts/KozGoPro-Light.otf");
    font.loadSubFont("Fonts/Futura.ttc");
    font.loadSubFont("Fonts/FiraCode-Regular.otf");
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
    if(!(spentFrames % 10 == 0)) return;
    if(!(agentNum < MAX_AGENTS)) return;
    //-------------------------------------------------
    //Dammy
    //-------------------------------------------------
    if(putDammyData){
        networkAgents.at(agentNum).validate(JsonReceiver::getInstance().getDammyUserNameData().at(ofRandom(4)));
        agentNum++;
        putDammyData = false;
    }
    //-------------------------------------------------
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
    ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
    ofSetLineWidth(5);
    for(int i = 0; i < agentNum; i++){
        int lineNum = 0;
        for(int j = i; j < agentNum && lineNum < agentNum/10.0; j++){
            if(networkAgents.at(i).NorP.at(j) < 0) {
                //ofSetColor(50, 255, 50, 150);
                ofSetColor(50, 255, 50, 255);
            }else{
                //ofSetColor(100, 255, 255, 150);
                ofSetColor(100, 255, 255, 255);
            }
            ofSetLineWidth(0.3);
            ofLine(networkAgents.at(i).position, networkAgents.at(j).position);
            lineNum++;
        }
    }
    for(int i = 0; i < agentNum; i++){
        glPushMatrix();
        glTranslatef(networkAgents.at(i).position.x, networkAgents.at(i).position.y, networkAgents.at(i).position.z);
        glRotatef(i * 10, 1, 0.1, -0.3);
        ofNoFill();
        ofSetColor(circleColor);
        ofSetLineWidth(5);
        ofCircle(0, 0, 50);
        ofFill();
        ofSetColor(nameColor);
        font.drawString(networkAgents.at(i).name,0,0,0);
        ofSetColor(circleColor);
        font.drawString(ofToString(networkAgents.at(i).position.x) + "\n" + ofToString(networkAgents.at(i).position.y) + "\n" + ofToString(networkAgents.at(i).position.z), 0, 20);
        glPopMatrix();
    }
    camera.end();
    ofDisableAlphaBlending();
    ofDisableBlendMode();
    ofDisableDepthTest();
    ofPopStyle();
    glPopMatrix();
}

void StringNetwork::updateAgents(){
    for(int i = 0; i< agentNum; i++){
        if((networkAgents.at(i).nextPosition - networkAgents.at(i).position).length() < 20
           || abs(networkAgents.at(i).position.x) > expandingArea ||abs(networkAgents.at(i).position.y) > expandingArea || abs(networkAgents.at(i).position.z) > expandingArea){
            networkAgents.at(i).position = ofVec3f(networkAgents.at(i).nextPosition.x,networkAgents.at(i).nextPosition.y,networkAgents.at(i).nextPosition.z);
            networkAgents.at(i).nextPosition = ofVec3f(ofRandom(-expandingArea,expandingArea),ofRandom(-expandingArea,expandingArea),ofRandom(-expandingArea,expandingArea));
            networkAgents.at(i).befPosition = networkAgents.at(i).position;
            networkAgents.at(i).moveFrame = ofRandom(60,300);
        }else{
            networkAgents.at(i).position +=  ofVec3f(networkAgents.at(i).nextPosition - networkAgents.at(i).befPosition) / float(networkAgents.at(i).moveFrame);
        }
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
            font.loadFont("Fonts/Gidole-Regular.ttf",fontSize,true,true,0.3f,0,true);
            font.loadSubFont("Fonts/KozGoPro-Light.otf");
            break;
        case 'n':
            fontSize--;
            font.loadFont("Fonts/Gidole-Regular.ttf",fontSize,true,true,0.3f,0,true);
            font.loadSubFont("Fonts/KozGoPro-Light.otf");
            break;
        case 'R':
            init();
            break;
        case 'P':
            putDammyData = true;
            break;
        default:
            break;
    }
}
void StringNetwork::onMouseDown(int x, int y){}