//
//  SingleAgentAnalyze.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/12.
//

#include "SingleAgentAnalyze.h"

void SingleAgentAnalyze::reset(){
    shiseido.reset();
    SingleUserManager::user_agent.clear();
}

void SingleAgentAnalyze::init(){

    SingleUserManager::json_num=0;
    check_is_json_new();
    for(int i = 0; i<SingleUserManager::user_agent.size();i++){
        SingleUserManager::user_agent.at(i)->init();
    }
    shiseido.init();
    max_row = ofGetHeight()/90 -1;
    max_column = ofGetWidth()/200-2;
    MAX_AGENT = (max_row)*(max_column+2);
}

void SingleAgentAnalyze::draw(){
    int agent_size = SingleUserManager::user_agent.size();
    float y;
    ofSetColor(255);
    if(MAX_AGENT < agent_size ){
        SingleUserManager::user_agent.erase(SingleUserManager::user_agent.begin());
    }

    agent_size = SingleUserManager::user_agent.size();
    
    int offset = 100;
    if(mode)offset = ofGetWidth()-600;
    if(agent_size>0){
        for(int i = 0; i < ((4<agent_size)?4:agent_size) ; i++){
            y = 200 * (i%max_row -1) +200;
            SingleUserManager::user_agent.at(agent_size-1-i)->draw(offset,y+150);
        }
    }
    shiseido.draw();
}


void SingleAgentAnalyze::update(){
    check_is_json_new();
}


void SingleAgentAnalyze::onMouseDown(int x, int y){
    
}

void SingleAgentAnalyze::keyPressed(int key){
    if(key ==OF_KEY_RETURN){
        if(shiseido.switch_mode()==3){
            mode = true;
        }else{
            mode = false;
        }
        ofxSuperLogUtil::set_log("switch mode","visualization changed");
    }else if(key == OF_KEY_TAB){
        reset();
    }
}

void SingleAgentAnalyze::end(){}

void SingleAgentAnalyze::check_is_json_new(){
    int add_num;
    if(SingleUserManager::json_num<JsonReceiver::getInstance().getUsersInfo().size()){
        add_num = JsonReceiver::getInstance().getUsersInfo().size() - SingleUserManager::json_num;
        addAgent(add_num);
        ofxSuperLogUtil::set_log("add agent","add "+ofToString(add_num)+" agents");
        shiseido.add_line_num(add_num);
    }
}

void SingleAgentAnalyze::addAgent(int add_num){
    ofVec2f pos;
    for(int i=0;i<add_num;i++){
        SingleUserManager::user_agent.push_back(new SingleAgent());
        SingleUserManager::user_agent.back()->init();
        SingleUserManager::user_agent.back()->get_info_from_twitter(
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).userName,
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).twitterId,
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).text,
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).friends_count,
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).statuses_count,
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).followers_count,
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).iconURL);
        ofxSuperLogUtil::set_log("Agent added",ofToString(JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).twitterId)+" join");
        SingleUserManager::json_num++;//json_numはここで
    }
}
