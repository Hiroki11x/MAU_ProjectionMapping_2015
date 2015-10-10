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

void UserAgent::get_info_from_twitter(string name,string id, string text,int friends_count,int statuses_count,int followers_count, ofImage image){
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

void UserAgent::update(){
    multiple_of_size = ofRandom(MIN_CIRCLE_MAGNIFICATION,MAX_CIRCLE_MAGNIFICATION);
}
void UserAgent::draw(){
    int angle;
    
    ofFill();
    ofSetColor(color);
    ofCircle(position, size * multiple_of_size/2);
    ofSetColor(255);
    icon.draw(position.x-15,position.y-15, 30,30);
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
    
//    ofLine(position+ofVec2f(0,size*2), position+ofVec2f(line_length,size*2));
//    ofLine(position+ofVec2f(0,-size*2), position+ofVec2f(line_length,-size*2));
    
    ofSetColor(color,255);
    FontManager::mfont.drawString(username, position.x+size*2.5,position.y-size+3);
    FontManager::mfont.drawString(id, position.x+size*2.5,position.y+3);
    FontManager::msmallfont.drawString("Follower:"+ofToString(followers_count), position.x+size*2.5,position.y+8);
    FontManager::msmallfont.drawString("Friends:"+ofToString(friends_count), position.x+size*2.5,position.y+13);
    FontManager::msmallfont.drawString("Statue:"+ofToString(statuses_count), position.x+size*2.5+50,position.y+8);
    
    /*
    font.drawString(ofToString(JsonReceiver::usersInfo.at(i).followers_count),position.at(i), pos_center_y-line_length-10);
    font.drawString(ofToString(JsonReceiver::usersInfo.at(i).statuses_count),position.at(i), pos_center_y-line_length-20);
    font.drawString(ofToString(JsonReceiver::usersInfo.at(i).friends_count),position.at(i), pos_center_y-line_length-30);
    font.drawString(JsonReceiver::usersInfo.at(i).userId,position.at(i), pos_center_y-line_length-40);
    font.drawString(JsonReceiver::usersInfo.at(i).userName,position.at(i), pos_center_y-line_length-50);
    font.drawString(JsonReceiver::usersInfo.at(i).text,position.at(i), pos_center_y-line_length-60);
     */
    
}

void UserAgent::draw_line(float line_x){
    ofLine(line_x, line_y1,line_x, line_y2);
    FontManager::mfont.drawString(username, line_x,line_y1);
    FontManager::mfont.drawString(id, line_x,line_y1+10);
    FontManager::mfont.drawString(text, line_x,line_y1+20);
}

void UserAgent::draw_circle(){
    float arg;
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofBeginShape();
    for(int i=0;i<240;i++){
        arg = ofRandom(2*PI);
        ofVertex(200*cos(arg), 200*sin(arg));
    }
    ofEndShape();
    icon.draw(-100,-100,200,200);
    ofPopMatrix();
}





