
//  AgentCircle.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/09.
//
//

#include "AgentCircle.h"

void AgentCircle::init(){
    ofSetCircleResolution(32);
    registertime = ofGetSystemTime();
}

void AgentCircle::get_info_from_twitter(string name,string id, wstring text,int friends_count,int statuses_count,int followers_count){
    //twitterからの取得情報を書く
    username = name;
    this->id = id;
    this->text = text;
    this->friends_count = friends_count;
    this->statuses_count = statuses_count;
    this->followers_count = followers_count;
}

void AgentCircle::update(){
}

