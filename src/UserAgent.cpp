//
//  UserAgent.cpp
//  MauInteractive
//
//  Created by HirokiNaganuma on 2015/09/12.
//
//

#include "UserAgent.h"


void UserAgent::init(){
    ofSetCircleResolution(32);
    registertime = ofGetSystemTime();
    set_size(DEFAULT_USER_CIRCLE_SIZE);
//    get_info_from_twitter();//twitterから情報取ってくる関数を呼ぶ
    calc_line_length();
    icon.allocate(30, 30,OF_IMAGE_COLOR);
    
}

void UserAgent::get_info_from_twitter(string name,string id, wstring text,int friends_count,int statuses_count,int followers_count, ofImage image){
    //twitterからの取得情報を書く
    username = name;
    this->id = id;
    this->text = text;
    this->friends_count = friends_count;
    this->statuses_count = statuses_count;
    this->followers_count = followers_count;
    icon = image;
    
    
}

void UserAgent::calc_line_length(){
    line_length = size * 40;
}

void UserAgent::set_position(ofVec2f _pos){
    position = _pos;
}

void UserAgent::set_size(float _size){
    size = _size;
}
void UserAgent::set_color(ofColor _color){
    color = _color;
}

void UserAgent::set_generater_index(int index){
    generater_index = index;
}

int UserAgent::get_generater_index(){
    return generater_index;
}


void UserAgent::update(){
    multiple_of_size = ofRandom(MIN_CIRCLE_MAGNIFICATION,MAX_CIRCLE_MAGNIFICATION);
}
void UserAgent::draw(){
//    int angle;
    
    ofFill();
//    ofSetColor(color);
//    ofCircle(position, size * multiple_of_size/2);
    ofSetColor(255);
    icon.draw(position.x-15,position.y-15, 30,30);
    ofNoFill();
    
//    ofBeginShape();//回転する内部の円
//    for(int i=0;i<240;i++){
//        angle = i + ofGetElapsedTimef()*50;
//        ofVec2f basis_vec =ofVec2f(sin(angle/180.0*PI), cos(angle/180.0*PI));
//        ofVec2f vec = position+ basis_vec*multiple_of_size*INNER_CIRCLE_MAGNIFICATION*size;
//        ofVertex(vec.x, vec.y);
//    }
//    ofEndShape();
//    
//    ofBeginShape();//回転する外部の円
//    for(int i=0;i<240;i++){
//        angle = 100 + i + ofGetElapsedTimef()*50;
//        ofVec2f basis_vec =ofVec2f(sin(-angle/180.0*PI), cos(-angle/180.0*PI));
//        ofVec2f vec = position + basis_vec*multiple_of_size*size;
//        ofVertex(vec.x, vec.y);
//    }
//    ofEndShape();
    
//    ofSetLineWidth(0.01);
    
//    ofLine(position+ofVec2f(0,size*2), position+ofVec2f(line_length,size*2));
//    ofLine(position+ofVec2f(0,-size*2), position+ofVec2f(line_length,-size*2));
 
    ofSetColor(color,255);
    
    glPushMatrix();
    glRotatef(180, 1,0,0);
    FontManager::mfont.drawString(username, position.x+size*2.5,-(position.y+8));
    FontManager::mfont.drawString(id, position.x+size*2.5,-(position.y-2));
    FontManager::msmallfont.drawString("Follower: "+ofToString(followers_count), position.x+size*2.5,-(position.y-10));
    FontManager::msmallfont.drawString("Friends: "+ofToString(friends_count), position.x+size*2.5,-(position.y-16));
    FontManager::msmallfont.drawString("Statue: "+ofToString(statuses_count), position.x+size*2.5+50,-(position.y-10));
    glPopMatrix();

}





