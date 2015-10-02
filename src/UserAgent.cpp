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
    get_info_from_twitter();//twitterから情報取ってくる関数を呼ぶ
    calc_line_length();
    
}

void UserAgent::get_info_from_twitter(){
    //twitterからの取得情報を書く
    icon;
    id = "ID:hoge";
    username = "hoge hoge";
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

void UserAgent::update(){
    multiple_of_size = ofRandom(MIN_CIRCLE_MAGNIFICATION,MAX_CIRCLE_MAGNIFICATION);
}
void UserAgent::draw(){
    int angle;
    
    ofFill();
    ofSetColor(color);
    ofCircle(position, size * multiple_of_size/2);
    
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
    
    ofSetLineWidth(0.1);
    ofLine(position+ofVec2f(0,size*2), position+ofVec2f(line_length,size*2));
    ofLine(position+ofVec2f(0,-size*2), position+ofVec2f(line_length,-size*2));
    
    ofDrawBitmapString(username, position+ofVec2f(size*2.5,-size+2));
    ofDrawBitmapString(id, position+ofVec2f(size*2.5,3));
    ofDrawBitmapString(ofToString(registertime), position+ofVec2f(size*2.5,size+4));
}






