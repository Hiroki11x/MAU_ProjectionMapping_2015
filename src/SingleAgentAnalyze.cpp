//
//  SingleAgentAnalyze.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/12.
//
//

#include "SingleAgentAnalyze.h"


void SingleAgentAnalyze::init(){
    json_num=0;
    check_is_json_new();
    for(int i = 0; i<user_agent.size();i++){
        user_agent.at(i).init();
    }
}

void SingleAgentAnalyze::draw(){
    
    int agent_size = user_agent.size();
    int max_row = ofGetHeight()/50 -2;
    int max_column = ofGetWidth()/170;
    
    ofSetColor(255);
    
    if((max_row+2)*max_column < agent_size ){
        user_agent.erase(user_agent.begin());
    }
    if(user_agent.size()>0)user_agent.back().draw();
    
}


void SingleAgentAnalyze::update(){
    JsonReceiver::recieve();
    check_is_json_new();
}


void SingleAgentAnalyze::onMouseDown(int x, int y){
    
}

void SingleAgentAnalyze::keyPressed(int key){
    
}

void SingleAgentAnalyze::end(){}

void SingleAgentAnalyze::check_is_json_new(){
    int add_num;
    if(json_num<JsonReceiver::usersInfo.size()){
        add_num = JsonReceiver::usersInfo.size() - json_num;
        addAgent(add_num);
    }
}



void SingleAgentAnalyze::addAgent(int add_num){
    ofVec2f pos;
    for(int i=0;i<add_num;i++){
        user_agent.push_back(SingleAgent());
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
