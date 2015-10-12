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

void SingleAgent::draw(){
    int angle;
    int hue;
    
    shiseido.draw();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofNoFill();
    
    //---------------FRIENDS---------------
    hue = ofMap(friends_count, 0, 1000, 0, 255);
    ofSetColor(ofColor::fromHsb(hue, 155, 200), 200);
    
    ofBeginShape();
    for(int i=0;i<100;i++){
        angle = i*hue + ofGetElapsedTimef()*50;
        ofVec2f basis_vec =ofVec2f(sin(angle/180.0*PI), cos(angle/180.0*PI));
        ofVec2f vec = basis_vec*OUTER_CIRCLE_MAGNIFICATION;
        ofVertex(vec.x, vec.y);
    }
    ofEndShape(false);
    //---------------FRIENDS---------------
    
    //---------------FOLLOWER---------------
    hue = ofMap(followers_count, 0, 1000, 0, 255);
    ofSetColor(ofColor::fromHsb(hue, 155, 200), 200);
    
    ofBeginShape();
    for(int i=0;i<100;i++){
        angle = i*hue + ofGetElapsedTimef()*50;
        ofVec2f basis_vec =ofVec2f(sin(angle/180.0*PI), cos(angle/180.0*PI));
        ofVec2f vec = basis_vec*INNER_CIRCLE_MAGNIFICATION;
        ofVertex(vec.x, vec.y);
    }
    ofEndShape(false);
    //---------------FOLLOWER---------------
    
    
    
    ofSetColor(255);
    ofFill();
    icon.draw(-50, -50, 100,100);
    ofPopMatrix();
    
    
}

void SingleAgent::draw_circle(float x, float y){
    int angle;
    
    ofPushMatrix();
    ofTranslate(x, y);
    ofFill();
    ofSetColor(255);
    icon.draw(0,0, 50,50);
    ofPopMatrix();
//    
//    ofBeginShape();//回転する内部の円
//    for(int i=0;i<240;i++){
//        angle = i + ofGetElapsedTimef()*50;
//        ofVec2f basis_vec =ofVec2f(sin(angle/180.0*PI), cos(angle/180.0*PI));
//        ofVec2f vec = position+ basis_vec*INNER_CIRCLE_MAGNIFICATION*size;
//        ofVertex(vec.x, vec.y);
//    }
//    ofEndShape();
//    
//    ofBeginShape();//回転する外部の円
//    for(int i=0;i<240;i++){
//        angle = 100 + i + ofGetElapsedTimef()*50;
//        ofVec2f basis_vec =ofVec2f(sin(-angle/180.0*PI), cos(-angle/180.0*PI));
//        ofVec2f vec = position + basis_vec*size;
//        ofVertex(vec.x, vec.y);
//    }
//    ofEndShape();

}
