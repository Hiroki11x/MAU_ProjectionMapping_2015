//
//  SingleAgent.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/12.
//
//

#include "SingleAgent.h"


void SingleAgent::init(){
    ofSetCircleResolution(32);
    registertime = ofGetSystemTime();
    icon.allocate(300, 300,OF_IMAGE_COLOR);
    set_position(ofVec2f(ofGetWidth()/2,ofGetHeight()/2));
}

void SingleAgent::get_info_from_twitter(string name,string id, string text,int friends_count,int statuses_count,int followers_count, ofImage image){
    //twitterからの取得情報を書く
    username = name;
    this->id = id;
    this->text = text;
    this->friends_count = friends_count;
    this->statuses_count = statuses_count;
    this->followers_count = followers_count;
    icon = image;
}

void SingleAgent::set_position(ofVec2f _pos){
    position = _pos;
}

void SingleAgent::set_size(float _size){
    size = _size;
}
void SingleAgent::set_color(ofColor _color){
    color = _color;
}

void SingleAgent::update(){
}

void SingleAgent::draw(float x, float y){
    int angle;
    int hue;
    
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofSetColor(255);
    ofFill();
    icon.draw(-50, -50, 100,100);
    FontManager::mfont.drawString(username, 70,0);
    FontManager::mfont.drawString(id, 70,10);
    FontManager::mfont.drawString("Follower: "+ofToString(followers_count), 70,20);
    FontManager::mfont.drawString("Friends: "+ofToString(friends_count), 70,30);
    FontManager::mfont.drawString("Statue: "+ofToString(statuses_count), 70,40);
    
    ofPopMatrix();
}


