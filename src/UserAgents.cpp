//
//  UserAgents.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/30.
//
//
#include "UserAgents.h"

void UserAgents::init(){
    setup_user_agent();
}

void UserAgents::update(){
    for(int i = 0; i < userAgentArray.size(); i++){
        userAgentArray.at(i)->update();
    }
}

void UserAgents::draw(){
    for(int i = 0; i < connections.size(); i++){
        connections.at(i)->drawConnection();
    }
    for(int i = 0; i < userAgentArray.size(); i++){
        userAgentArray.at(i)->draw();
    }
}

void UserAgents::onMouseDown(int x, int y){}

void UserAgents::end(){}

void UserAgents::addAgent(ofVec2f position){
    userAgentArray.push_back(new UserAgent());
    userAgentArray.back()->set_position(position);
    userAgentArray.back()->set_color(ofColor::fromHsb(100, COLOR_MAX, ofRandom(150,COLOR_MAX)));
    userAgentArray.back()->set_size(10);
    userAgentArray.back()->init();
    userAgentsSize += 1;
}

void UserAgents::addConnection(int startIndex,int endIndex,float duration){
    if(startIndex >= userAgentsSize || endIndex >= userAgentsSize || startIndex == endIndex){return;}
    connections.push_back(new Connection(userAgentArray.at(startIndex)->position,
                                         userAgentArray.at(endIndex)->position,
                                         ofColor::fromHsb(100, COLOR_MAX, ofRandom(150,COLOR_MAX)),
                                         duration
                                         ));
}

int UserAgents::getUserAgentSize(){
    return userAgentsSize;
}
int UserAgents::getConnectionSize(){
    return 0;
}

void UserAgents::setup_user_agent(){
    matrix_generator.generate_position(6, 12);//6*12個の座標を生成
    for(int j=0;j<30;j++){
        userAgentArray.push_back(new UserAgent());
        int size = matrix_generator.get_position_num();
        int index = ofRandom(size);
        while(matrix_generator.get_is_used().at(index)){
            index = ofRandom(size);
        }
        matrix_generator.set_is_used_true(index);
        ofVec2f position = *matrix_generator.get_position().at(index);
        
        userAgentArray.back()->set_position(position);
        //        user_agent.back()->set_position(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
        
        userAgentArray.back()->set_color(ofColor::fromHsb(ofRandom(COLOR_MAX), COLOR_MAX, COLOR_MAX));
        userAgentArray.back()->set_size(10);
        userAgentArray.back()->init();
    }
}