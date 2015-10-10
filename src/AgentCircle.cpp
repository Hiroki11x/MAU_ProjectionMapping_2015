
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
    set_size(DEFAULT_USER_CIRCLE_SIZE);
    icon.allocate(300, 300,OF_IMAGE_COLOR);
    set_position(ofVec2f(ofGetWidth()/2,ofGetHeight()/2));
}

void AgentCircle::get_info_from_twitter(string name,string id, string text,int friends_count,int statuses_count,int followers_count, ofImage image){
    //twitterからの取得情報を書く
    username = name;
    this->id = id;
    this->text = text;
    this->friends_count = friends_count;
    this->statuses_count = statuses_count;
    this->followers_count = followers_count;
    icon = image;
}

void AgentCircle::set_position(ofVec2f _pos){
    position = _pos;
}

void AgentCircle::set_size(float _size){
    size = _size;
}
void AgentCircle::set_color(ofColor _color){
    color = _color;
}

void AgentCircle::update(){
}
void AgentCircle::draw_line(float x, float y){
    ofPushMatrix();
    ofTranslate(x, y);
    FontManager::mfont.drawString(username, 0,0);
    FontManager::mfont.drawString(id, 0,10);
    FontManager::mfont.drawString("Follower:"+ofToString(followers_count), 0,20);
    FontManager::mfont.drawString("Friends:"+ofToString(friends_count), 0,30);
    FontManager::mfont.drawString("Statue:"+ofToString(statuses_count), 0,40);
    ofPopMatrix();
}

void AgentCircle::draw_circle(){
    int angle;
    
    ofFill();
    ofSetColor(color);
    ofCircle(position, size * multiple_of_size/2);
    ofSetColor(255);
    icon.draw(position.x-150,position.y-150, 300,300);
    ofSetColor(color);
    ofNoFill();
    
    ofBeginShape();//回転する内部の円
    for(int i=0;i<240;i++){
        angle = i + ofGetElapsedTimef()*50;
        ofVec2f basis_vec =ofVec2f(sin(angle/180.0*PI), cos(angle/180.0*PI));
        ofVec2f vec = position+ basis_vec*multiple_of_size*INNER_CIRCLE_MAGNIFICATION*size;
        ofVertex(vec.x, vec.y);
    }
    ofEndShape();
    
    ofBeginShape();//回転する外部の円
    for(int i=0;i<240;i++){
        angle = 100 + i + ofGetElapsedTimef()*50;
        ofVec2f basis_vec =ofVec2f(sin(-angle/180.0*PI), cos(-angle/180.0*PI));
        ofVec2f vec = position + basis_vec*multiple_of_size*size;
        ofVertex(vec.x, vec.y);
    }
    ofEndShape();
    
    ofSetLineWidth(0.01);

    ofSetColor(color,255);
    FontManager::mfont.drawString(username, position.x+size*2.5,position.y-size+3);
    FontManager::mfont.drawString(id, position.x+size*2.5,position.y+3);
    FontManager::mfont.drawString(text, position.x+size*2.5,position.y+13);
    FontManager::mfont.drawString("Follower:"+ofToString(followers_count), position.x+size*2.5,position.y+23);
    FontManager::mfont.drawString("Friends:"+ofToString(friends_count), position.x+size*2.5,position.y+33);
    FontManager::mfont.drawString("Statue:"+ofToString(statuses_count), position.x+size*2.5,position.y+43);
    
}
