//
//  UserAgent.cpp
//  MauInteractive
//
//  Created by HirokiNaganuma on 2015/09/12.
//
//

#include "UserAgent.h"


void UserAgent::init(){
    registertime = ofGetSystemTime();
    get_info_from_twitter();//twitterから情報取ってくる関数を呼ぶ
}

void UserAgent::get_info_from_twitter(){
    //twitterからの取得情報を書く
    icon;
    id = "ID:hoge";
    username = "hoge hoge";
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
    multiple_of_size = ofRandom(1.5,2.5);
    
}
void UserAgent::draw(){
    ofFill();
    ofSetColor(color);
    ofCircle(position, size);
    
    ofNoFill();
    
    ofBeginShape();
    for(int i=0;i<240;i++){
        int angle = i + ofGetElapsedTimef()*50;
        ofVec2f basis_vec =ofVec2f(sin(angle/180.0*PI), cos(angle/180.0*PI));
        ofVec2f vec = position+ basis_vec*multiple_of_size*(3/4.0f)*size;
        ofVertex(vec.x, vec.y);
    }
    ofEndShape();
    
    ofBeginShape();
    for(int i=0;i<240;i++){
        int angle = 100 + i + ofGetElapsedTimef()*50;
        ofVec2f basis_vec =ofVec2f(sin(-angle/180.0*PI), cos(-angle/180.0*PI));
        ofVec2f vec = position+ basis_vec*multiple_of_size*size;
        ofVertex(vec.x, vec.y);
    }
    ofEndShape();
    
    ofLine(position+ofVec2f(0,size*2), position+ofVec2f(300,size*2));
    ofLine(position+ofVec2f(0,-size*2), position+ofVec2f(300,-size*2));
    
    ofDrawBitmapString(username, position+ofVec2f(size*2.5,10));
    ofDrawBitmapString(id, position+ofVec2f(size*2.5,30));
    ofDrawBitmapString(ofToString(registertime), position+ofVec2f(size*2.5,50));
}






