//
//  SingleAgent.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/12.
//
//

#include "SingleAgent.h"

void SingleAgent::init(){
    path.setCircleResolution(50);
    path.setFilled(true);
    path.setStrokeWidth(0.01);
    path.setHexColor(0x00ff0055);
    path2.setCircleResolution(50);
    path2.setFilled(true);
    path2.setStrokeWidth(0.01);
    path2.setHexColor(0xff440055);
    ofSetCircleResolution(32);
    path.setMode(ofPath::POLYLINES);
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

wstring SingleAgent::get_user_text(){
    return this->text;
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

void SingleAgent::draw(float x, float y){//画像の色解析４枚のやつ

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
    float x_start;
    float args;
    for(int i =0;i<3;i++){
        x_start = i*42+80;
        if(i==0){
            args = followers_count/20.0f;
        }else if(i == 1){
            args = friends_count/20.0;
        }else{
            args = statuses_count/100.0f;
        }
        path.clear();
        path2.clear();
        path.moveTo(x_start,-30);
        path.arc(x_start, -30, 15, 15, 0, args);
        path.lineTo(x_start,-30);
        path2.moveTo(x_start,-30);
        path2.arc(x_start, -30, 15, 15,args , 360);
        path2.lineTo(x_start,-30);
        path.draw();
        path2.draw();
    }
    ofPopMatrix();
}

void SingleAgent::draw_line(float x, float y){//2D文字だけ
    ofPushMatrix();
    ofTranslate(x, y);
    ofFill();
    if(id.length()<8){
        ofSetColor(255,0,0,ofRandom(0,170));
    }else{
        ofSetColor(0,255,0,ofRandom(0,170));
    }
    ofRect(0,-10,150,10);
    ofSetColor(255);
    FontManager::mfont.drawString(username, 0,0);
    FontManager::mfont.drawString(id, 0,10);
    FontManager::mfont.drawString("Follower: "+ofToString(followers_count), 0,20);
    FontManager::mfont.drawString("Friends: "+ofToString(friends_count), 0,30);
    FontManager::mfont.drawString("Statue: "+ofToString(statuses_count), 0,40);
    ofPopMatrix();
}

void SingleAgent::draw_line(float x, float y,float z){//3D文字だけ
    ofPushMatrix();
    ofTranslate(x, y, z);
    ofFill();
    if(id.length()<8){
        ofSetColor(255,0,0,ofRandom(0,170));
    }else{
        ofSetColor(0,255,0,ofRandom(0,170));
    }
    
    ofRect(0,0,150,10);
    ofSetColor(255);
    
    glPushMatrix();
    glRotatef(180, 1,0,0);
//    glTranslated(x, y, z);
    FontManager::mfont.drawString(username, 0,0);
    FontManager::mfont.drawString(id, 0,10);
    FontManager::mfont.drawString("Follower: "+ofToString(followers_count), 0,20);
    FontManager::mfont.drawString("Friends: "+ofToString(friends_count), 0,30);
    FontManager::mfont.drawString("Statue: "+ofToString(statuses_count), 0,40);
    glPushMatrix();
    ofPopMatrix();
}


