//
//  SpyMeshSceneGui.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/16.
//
//
#include "SpyMeshSceneGui.h"

void SpyMeshSceneGui::init(){
    float fontSize = 10;
    font = new ofxTrueTypeFontUL2();
    font->loadFont("Arial.ttf", fontSize);
    font->loadSubFont("YuMincho");
    font->loadSubFont(OF_TTF_SERIF,1.2,-0.02);
    font->loadSubFont("Geeza Pro",1,-0.04,0x0600,0x06FF,"arab");
    font->useProportional(true);
    font->useVrt2Layout(true);
    font->setLineHeight(font->getFontSize()*1.5);
    nameFont = new ofxTrueTypeFontUL2();
    nameFont->loadFont("Arial.ttf", fontSize);
    nameFont->loadSubFont("YuMincho");
    nameFont->loadSubFont(OF_TTF_SERIF,1.2,-0.02);
    nameFont->loadSubFont("Geeza Pro",1,-0.04,0x0600,0x06FF,"arab");
    nameFont->useProportional(true);
    nameFont->useVrt2Layout(true);
    nameFont->setLineHeight(nameFont->getFontSize()*1.5);
    befAgentNum = 0;
}

void SpyMeshSceneGui::drawGui(vector<AgentAnalysis> agents){
    ofPushMatrix();
    ofPushStyle();
    
    drawBackLine();
    drawEntry(agents);
    
    ofPopMatrix();
    ofPushStyle();
}

void SpyMeshSceneGui::updateGui(){
    for(int i = 0; i < newAgentWaves.size(); i++){
        newAgentWaves.at(i).size += ofRandom(1.0, 10.0);
        if(newAgentWaves.at(i).size > 1500){
            newAgentWaves.erase(newAgentWaves.begin() + i);
            i--;
        }
    }
}


void SpyMeshSceneGui::drawEntry(vector<AgentAnalysis> agents){
    
    ofSetColor(50,50,50,100);
    ofRect(50, 100 , 200 , 20 + 30 * agents.size());
    ofNoFill();
    ofSetColor(130, 255, 130,180);
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
        ofSetColor(200, 255, 200,180);
        nameFont->drawString(agents.at(i).userName, 10, 20);
        ofSetColor(80, 230, 80, 150);
        ofRect(5, 5, 190.0 * (float)agents.at(i).mesh.vertices.size() / 3000.0, 20);
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

class SpyMeshSceneGui::EntryEntity{
public:
};
