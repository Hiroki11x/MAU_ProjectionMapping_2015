//
//  ParticleElement.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/08.
//
//

#include "ParticleElement.h"


bool ParticleElement::is_fade(){
    return isfade;
}

void ParticleElement::set_color(ofColor arg_color){
    color = arg_color;
}

ofVec2f* ParticleElement::get_position(){
    return &position;
}

void ParticleElement::set_size(float size){
    this->size =size;
}

void ParticleElement::set_speed(ofVec2f speed){
    this->speed = speed;
}

void ParticleElement::set_position(ofVec2f position){
    this->position = position;
}


void ParticleElement::init(){
    
}

void ParticleElement::update(){
    if(position.x<ofGetWidth()+OFFSET && position.x> -OFFSET){
        position.x += speed.x;
    }else{
        isfade =true;
    }
    if(position.y<ofGetHeight()+OFFSET && position.y> -OFFSET){
        position.y += speed.y;
    }else{
        isfade =true;
    }
}

void ParticleElement::draw(){
    //以下をTriangle書くときにまとめて呼ぶ
    //    ofPushStyle()
    //    ofSetCircleResolution(60);
    update();
    
    ofPushMatrix();
    ofTranslate(position);
    ofSetColor(color,255);
    ofCircle(0,0,size);
    ofSetColor(color, ofRandom(255));
    ofCircle(0,0,size*2);
    ofSetColor(color, ofRandom(155));
    ofCircle(0,0,size*4);
    ofPopMatrix();
}