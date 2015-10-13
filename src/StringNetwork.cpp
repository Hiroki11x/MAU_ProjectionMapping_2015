//
//  StringNetwork.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/13.
//
//
#include "StringNetwork.h"

void StringNetwork::init(){
    font.loadFont("Arial.ttf", 10);
    font.loadFont("Yumin Demibold",32,true,true,0.3f,0,true)||font.loadSubFont("YuMincho");
    font.loadSubFont(OF_TTF_SERIF,1.2,-0.02);
    font.loadSubFont("Geeza Pro",1,-0.04,0x0600,0x06FF,"arab");
    font.useProportional(true);
    font.useVrt2Layout(true);
    font.setLineHeight(font.getFontSize()*1.5);
}

void StringNetwork::update(){}

void StringNetwork::draw(){
    camera.begin();
    
    
    camera.end();
}

void StringNetwork::onMouseDown(int x, int y){}

void StringNetwork::keyPressed(int key){}

class StringNetwork::NetworkAgent{
public:
    ofVec2f possition;
    vector<NetworkAgent> connectedAgents;
    wstring name;
    
    void updatePosition();
};