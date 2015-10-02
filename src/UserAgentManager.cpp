//
//  UserAgentManeger.cpp
//  MauInteractive
//
//  Created by SakuragiYoshimasa on 2015/09/12.
//
//
#include "UserAgentManager.h"

void UserAgentManager::addAgent(ofVec2f position){
    userAgents.push_back(new UserAgent());
    userAgents.back()->set_position(position);
    userAgents.back()->set_color(ofColor::fromHsb(100, COLOR_MAX, ofRandom(150,COLOR_MAX)));
    userAgents.back()->set_size(10);
    userAgents.back()->init();
    userAgentsSize += 1;
}

void UserAgentManager::addConnection(int startIndex,int endIndex,float duration){
    if(startIndex >= userAgentsSize || endIndex >= userAgentsSize || startIndex == endIndex){return;}
    connections.push_back(new Connection(userAgents.at(startIndex)->position,
                                         userAgents.at(endIndex)->position,
                                         ofColor::fromHsb(100, COLOR_MAX, ofRandom(150,COLOR_MAX)),
                                         duration
                                         ));
}

void UserAgentManager::update(){
    for(int i = 0; i < userAgents.size(); i++){ userAgents.at(i)->update();}
}

void UserAgentManager::draw(){
    for(int i = 0; i < connections.size(); i++){ connections.at(i)->drawConnection();}
    for(int i = 0; i < userAgents.size(); i++){ userAgents.at(i)->draw();}
}

int UserAgentManager::getUserAgentSize(){return userAgentsSize;}
int UserAgentManager::getConnectionSize(){return 0;}
