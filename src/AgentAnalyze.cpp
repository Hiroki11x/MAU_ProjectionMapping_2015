
//
//  AgentAnalyze.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/09.
//
//

#include "AgentAnalyze.h"



void AgentAnalyze::init(){
    for(int j=0;j<JsonReceiver::usersInfo.size();j++){//GENE_Y_NUM*GENE_X_NUM;
        addAgent(1);
    }
}

void AgentAnalyze::update(){

}

void AgentAnalyze::draw(){
    ofSetColor(255);
    ofCircle(300,300,ofRandom(300));
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
        
        /*
        userAgentArray.push_back(new UserAgent());
        pos = select_position();
        userAgentArray.back()->set_position(pos);
        userAgentArray.back()->set_color(ofColor::fromHsb(ofRandom(COLOR_MAX/4,COLOR_MAX/3), ofRandom(COLOR_MAX/4,COLOR_MAX), ofRandom(COLOR_MAX/4,COLOR_MAX)));
        userAgentArray.back()->init();
        userAgentArray.back()->set_size(USER_CIRCLE_SIZE);
        userAgentArray.back()->get_info_from_twitter(
                                                     JsonReceiver::usersInfo.at(json_num).userName,
                                                     JsonReceiver::usersInfo.at(json_num).twitterId,
                                                     JsonReceiver::usersInfo.at(json_num).text,
                                                     JsonReceiver::usersInfo.at(json_num).friends_count,
                                                     JsonReceiver::usersInfo.at(json_num).statuses_count,
                                                     JsonReceiver::usersInfo.at(json_num).followers_count,
                                                     JsonReceiver::usersInfo.at(json_num).icon);
        createExplodeAnimation(pos);
         */
        json_num++;//json_numはここで
    }
}



int AgentAnalyze::getUserAgentSize(){
//    return userAgentArray.size();
}

