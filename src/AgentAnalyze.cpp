
//
//  AgentAnalyze.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/09.
//
//


#include "AgentAnalyze.h"


void AgentAnalyze::reset(){
//    user_agent.clear();ここは画像取得もなく重くないのでクリアしない
}

void AgentAnalyze::init(){
    json_num=0;
    check_is_json_new();
    for(int i = 0; i<SingleUserManager::user_agent.size();i++){
        SingleUserManager::user_agent.at(i)->init();
    }
    max_row = ofGetHeight()/50 -2;
    max_column = ofGetWidth()/170;
    MAX_AGENT = (max_row+2)*max_column;
    
    graphlog.setup();
    graphlog.set_height_limit(ofGetWidth()/4);
}

void AgentAnalyze::draw(){
    if(mode){
        draw_2D();
    }else{
        draw_3D();
    }
}

void AgentAnalyze::draw_3D(){
    int agent_size = SingleUserManager::user_agent.size();
    ofSetColor(255);
    if(MAX_AGENT < agent_size ){
        SingleUserManager::user_agent.erase(SingleUserManager::user_agent.begin());
    }
    
    float x;
    float y;
    for(int i = 0; i< agent_size ;i++){
        if(i == agent_size-1){
            //            user_agent.at(i).draw_circle();
        }else{
            x = (i/max_row)*170 ;
            y = 60 * (i%max_row -1);
            SingleUserManager::user_agent.at(i)->draw_line(x+60,y+100,100*ofSignedNoise(ofGetElapsedTimef()/100));
        }
    }
    graphlog.draw();
}

void AgentAnalyze::draw_2D(){
    int agent_size = SingleUserManager::user_agent.size();
    ofSetColor(255);
    if(MAX_AGENT < agent_size ){
        SingleUserManager::user_agent.erase(SingleUserManager::user_agent.begin());
    }
    
    float x;
    float y;
    for(int i = 0; i< agent_size ;i++){
        if(i == agent_size-1){
            //            user_agent.at(i).draw_circle();
        }else{
            x = (i/max_row)*170 ;
            y = 60 * (i%max_row -1);
            SingleUserManager::user_agent.at(i)->draw_line(x+60,y+100);
        }
    }
    graphlog.draw();
}


void AgentAnalyze::update(){
    check_is_json_new();
}


void AgentAnalyze::onMouseDown(int x, int y){

}

void AgentAnalyze::keyPressed(int key){//Enterで2D,3Dを切り替え
    graphlog.keyPressed(key);
    if(key==OF_KEY_RETURN){
        mode = !mode;
    }
}

void AgentAnalyze::end(){}

void AgentAnalyze::check_is_json_new(){
    int add_num;
    if(json_num<JsonReceiver::getInstance().getUsersInfo().size()){
        add_num = JsonReceiver::getInstance().getUsersInfo().size() - json_num;
        addAgent(add_num);
        ofxSuperLogUtil::set_log("add agent","add "+ofToString(add_num)+" agents");
    }
}


void AgentAnalyze::addAgent(int add_num){
    ofVec2f pos;
    for(int i=0;i<add_num;i++){
        SingleUserManager::user_agent.push_back(new SingleAgent());
        SingleUserManager::user_agent.back()->init();
        SingleUserManager::user_agent.back()->get_info_from_twitter(
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).userName,
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).twitterId,
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).text,
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).friends_count,
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).statuses_count,
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).followers_count,
                                                JsonReceiver::getInstance().getUsersInfo().at(json_num).iconURL);
        ofxSuperLogUtil::set_log("Agent added",ofToString(JsonReceiver::getInstance().getUsersInfo().at(json_num).twitterId)+" join");
        json_num++;//json_numはここで
        graphlog.update(ofSignedNoise(json_num,ofRandom(100),ofGetElapsedTimef()));
    }
}
