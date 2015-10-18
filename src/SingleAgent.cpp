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

string SingleAgent::get_user_name(){
    return this->username;
}

string SingleAgent::get_user_id(){
    return this->id;
}

void SingleAgent::get_info_from_twitter(string name,string id, wstring text,int friends_count,int statuses_count,int followers_count, ofImage image){
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
    
    unsigned char * pixels =icon.getPixels();
    int w = icon.width;
    int h = icon.height;
    
    for (int i = 0; i < w; i+=8){
        for (int j = 0; j < h; j+=8){
            int valueR = pixels[j*3 * w + i*3];
            int valueG = pixels[j*3 * w + i*3+1];
            int valueB = pixels[j*3 * w + i*3+2];
            ofSetColor(255, 0, 0, 83);
            ofCircle(200+i, j-50, 6*valueR/255.0);
            ofSetColor(0, 255, 0, 83);
            ofCircle(200+i, j, 6*valueG/255.0);
            ofSetColor(0, 0, 255, 83);
            ofCircle(250+i, j-50, 6*valueB/255.0);
        }
    }
    
    ofPopMatrix();
}

void SingleAgent::draw_line(float x, float y){
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


