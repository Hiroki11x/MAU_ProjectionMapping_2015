
//
//  AgentAnalyze.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/09.
//
//


#include "AgentAnalyze.h"


void AgentAnalyze::init(){
    json_num=0;
    check_is_json_new();
    for(int i = 0; i<user_agent.size();i++){
        user_agent.at(i).init();
    }
}

void AgentAnalyze::draw(){
    ofCircle(20,20,10);
    float line_x;
    for(int i = 0; i<user_agent.size();i++){
        if(i == index){
            user_agent.at(i).draw_circle();
        }else{
            line_x = ofMap(i, 0, user_agent.size(), 0, ofGetWidth());
            user_agent.at(i).draw_line(line_x);
        }
    }
}


void AgentAnalyze::update(){
    check_is_json_new();
}


void AgentAnalyze::onMouseDown(int x, int y){

}

void AgentAnalyze::keyPressed(int key){
    
}

void AgentAnalyze::end(){}

void AgentAnalyze::check_is_json_new(){
    int add_num;
    if(json_num<JsonReceiver::usersInfo.size()){
        add_num = JsonReceiver::usersInfo.size() - json_num;
        addAgent(add_num);
    }
}



void AgentAnalyze::addAgent(int add_num){
    ofVec2f pos;
    for(int i=0;i<add_num;i++){
        user_agent.push_back(AgentCircle());
        user_agent.back().set_color(ofColor::fromHsb(ofRandom(COLOR_MAX/4,COLOR_MAX/3), ofRandom(COLOR_MAX/4,COLOR_MAX), ofRandom(COLOR_MAX/4,COLOR_MAX)));
        user_agent.back().init();
        user_agent.back().get_info_from_twitter(
                                                   JsonReceiver::usersInfo.at(json_num).userName,
                                                   JsonReceiver::usersInfo.at(json_num).twitterId,
                                                   JsonReceiver::usersInfo.at(json_num).text,
                                                   JsonReceiver::usersInfo.at(json_num).friends_count,
                                                   JsonReceiver::usersInfo.at(json_num).statuses_count,
                                                   JsonReceiver::usersInfo.at(json_num).followers_count,
                                                   JsonReceiver::usersInfo.at(json_num).icon);

        json_num++;//json_numはここで
    }
}
