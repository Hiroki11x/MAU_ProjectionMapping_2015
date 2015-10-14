
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
void AgentCircle::draw_line(float x, float y){
    ofPushMatrix();
    ofTranslate(x, y);
    ofFill();
    ofSetColor(0,255,0,ofRandom(0,170));
    ofRect(0,-10,150,10);
    ofSetColor(255);
    FontManager::mfont.drawString(username, 0,0);
    FontManager::mfont.drawString(id, 0,10);
    FontManager::mfont.drawString("Follower: "+ofToString(followers_count), 0,20);
    FontManager::mfont.drawString("Friends: "+ofToString(friends_count), 0,30);
    FontManager::mfont.drawString("Statue: "+ofToString(statuses_count), 0,40);
    ofPopMatrix();
}
