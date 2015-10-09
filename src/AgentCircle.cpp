//
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
    icon.allocate(30, 30,OF_IMAGE_COLOR);

    font.loadFont("Yu Gothic Medium.otf",8);
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
    multiple_of_size = ofRandom(MIN_CIRCLE_MAGNIFICATION,MAX_CIRCLE_MAGNIFICATION);
}
void AgentCircle::draw_line(float line_x){
    ofLine(line_x, line_y1,line_x, line_y2);
    font.drawString(username, line_x,line_y1);
}

void AgentCircle::draw_circle(){
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

    ofSetColor(color,255);
    font.drawString(username, position.x+size*2.5,position.y-size+3);
    font.drawString(id, position.x+size*2.5,position.y+3);
    font.drawString(text, position.x+size*2.5,position.y+13);
    font.drawString("Follower:"+ofToString(followers_count), position.x+size*2.5,position.y+23);
    font.drawString("Friends:"+ofToString(friends_count), position.x+size*2.5,position.y+33);
    font.drawString("Statue:"+ofToString(statuses_count), position.x+size*2.5,position.y+43);
}
