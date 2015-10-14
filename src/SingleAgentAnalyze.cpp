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
    shiseido.init();
    max_row = ofGetHeight()/50 -2;
    max_column = ofGetWidth()/170;
    
    MAX_AGENT = (max_row+2)*max_column;
}

void SingleAgentAnalyze::draw(){

    int agent_size = user_agent.size();

    float y;
    
    ofSetColor(255);
//    cout<<"max_size]]]]"<<(max_row+2)*max_column <<endl;
    if(MAX_AGENT < agent_size ){
        user_agent.erase(user_agent.begin());
    }

    agent_size = user_agent.size();
    
    if(agent_size>0){
        for(int i = 0; i < ((4<agent_size)?4:agent_size) ; i++){
            y = 200 * (i%max_row -1) +200;
            user_agent.at(agent_size-1-i).draw(100,y+100);
        }
    }
    shiseido.draw(user_agent.size());
    
}


void SingleAgentAnalyze::update(){
//    JsonReceiver::getInstance().recieve();
    check_is_json_new();
}


void SingleAgentAnalyze::onMouseDown(int x, int y){
    
}

void SingleAgentAnalyze::keyPressed(int key){
    if(key == 'p'){
        mode = !mode;
    }else if(key =='q'){
        shiseido.switch_mode();
    }
}

void SingleAgentAnalyze::end(){}

void SingleAgentAnalyze::check_is_json_new(){
    int add_num;
    if(json_num<JsonReceiver::getInstance().getUsersInfo().size()){
        add_num = JsonReceiver::getInstance().getUsersInfo().size() - json_num;
        addAgent(add_num);
    }
}



void SingleAgentAnalyze::addAgent(int add_num){
    ofVec2f pos;
    for(int i=0;i<add_num;i++){
        user_agent.push_back(SingleAgent());
        user_agent.back().init();
        user_agent.back().get_info_from_twitter(
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).userName,
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).twitterId,
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).text,
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).friends_count,
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).statuses_count,
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).followers_count,
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).iconURL);
        
        json_num++;//json_numはここで
    }
}