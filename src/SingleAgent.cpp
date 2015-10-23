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
    path.setColor(ofColor(0,250,0,255));
    path2.setCircleResolution(50);
    path2.setFilled(false);
    path2.setStrokeWidth(1);
    path2.setColor(ofColor(0,250,0,255));
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
    FontManager::mfont.drawString(username, 70,-2);
    FontManager::mfont.drawString(id, 70,12);
    FontManager::mfont.drawString("Follower: "+ofToString(followers_count), 70,26);
    FontManager::mfont.drawString("Friends: "+ofToString(friends_count), 70,40);
    FontManager::mfont.drawString("Statue: "+ofToString(statuses_count), 70,52);
    
    unsigned char * pixels =icon.getPixels();
    int w = icon.width;
    int h = icon.height;
    
    for (int i = 0; i < w; i+=8){
        for (int j = 0; j < h; j+=8){
            int valueR = pixels[j*3 * w + i*3];
            int valueG = pixels[j*3 * w + i*3+1];
            int valueB = pixels[j*3 * w + i*3+2];
            ofSetColor(255, 0, 0, 103);
            ofCircle(200+i, j-50, 6*valueR/255.0);
            ofSetColor(0, 255, 0, 103);
            ofCircle(200+i, j, 6*valueG/255.0);
            ofSetColor(0, 0, 255, 103);
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
        path.moveTo(x_start,-37);
        path.circle(x_start, -37, 5);
        path.arc(x_start, -37, 15, 15, 0, args);
        path.lineTo(x_start,-37);
        path2.circle(x_start, -37, 15);
        path2.moveTo(x_start,-37);
        path2.arc(x_start, -37, 15, 15,args , 360);
        path2.lineTo(x_start,-37);
        path.draw();
        path2.draw();
        ofSetColor(0,255,0,255);
        ofCircle(x_start, -37, 9);
        ofSetColor(0);
        ofCircle(x_start, -37, 8);
        ofSetColor(0,255,0,255);
        ofDrawBitmapString(ofToString(random_char[(int)args%7]), x_start-4,-31);
    }
    ofPopMatrix();
}

void SingleAgent::draw_line(float x, float y){//2D文字だけ
    ofPushMatrix();
    ofTranslate(x, y);
    ofFill();
    if(id.length()<8){
        ofSetColor(255,0,0,ofRandom(100,255));
    }else{
        ofSetColor(0,255,0,ofRandom(100,255));
    }
    ofRect(0,-16,180,16);
    ofSetColor(255);
    FontManager::mbigfont.drawString(username, 0,0);
    FontManager::mfont.drawString(id, 0,14);
    FontManager::mfont.drawString("Follower: "+ofToString(followers_count), 0,26);
    FontManager::mfont.drawString("Friends: "+ofToString(friends_count), 0,38);
    FontManager::mfont.drawString("Statue: "+ofToString(statuses_count), 0,50);
    ofPopMatrix();
}

void SingleAgent::draw_line(float x, float y,float z){//3D文字だけ
    ofPushMatrix();
    ofTranslate(x, y, z);
    ofFill();
    if(id.length()<8){
        ofSetColor(255,0,0,ofRandom(30,170));
    }else{
        ofSetColor(0,255,0,ofRandom(30,170));
    }
    
    ofRect(0,0,150,16);
    ofSetColor(255);
    
    glPushMatrix();
    glRotatef(180, 1,0,0);
//    glTranslated(x, y, z);
    FontManager::mbigfont.drawString(username, 0,0);
    FontManager::mfont.drawString(id, 0,14);
    FontManager::mfont.drawString("Follower: "+ofToString(followers_count), 0,26);
    FontManager::mfont.drawString("Friends: "+ofToString(friends_count), 0,38);
    FontManager::mfont.drawString("Statue: "+ofToString(statuses_count), 0,50);
    glPushMatrix();
    ofPopMatrix();
}


