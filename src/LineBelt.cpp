//
//  LineBelt.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/23.
//
//

#include "LineBelt.h"


void LineBelt::add_line_num(int add){//新たに追加していくやつ
    line_num+=add;
    for(int i = 0;i<add;i++){
        color.push_back(ofColor::fromHsb(ofRandom(255), 190, 190));
        position.push_back(ofRandom(ofGetWidth()));
    }
}

void LineBelt::reset_belt(){
    color.clear();
    position.clear();
    setup_belt(20);
}

void LineBelt::set_mode(){
    mode = !mode;
}

void LineBelt::set_center_y(float y){
    pos_center_y = y;
}

void LineBelt::set_line_num(int line_num){
    this->line_num = line_num;
}

void LineBelt::generate_position(){
    for(int i = 0;i<line_num;i++){
        position.push_back(ofRandom(ofGetWidth()));
    }
}

void LineBelt::generate_color(){
    for(int i = 0;i<line_num;i++){
        color.push_back(ofColor::fromHsb(ofRandom(255), 190, 255));
    }
}


void LineBelt::set_line_length(float line_length){
    this->line_length = line_length;
}


void LineBelt::setup_belt(int num){
    set_line_num(num);
    set_line_length(200);
    set_center_y(ofGetHeight()/2);
    generate_position();
    generate_color();
}

void LineBelt::update_belt(){
    for(int i = 0;i<line_num;i++){
        float addition_x = ofRandom(-3,3);
        if(!(position.at(i)+addition_x >ofGetWidth()) && !(position.at(i)+addition_x <0)){
            if(!mode){//元はこれ
                position.at(i)+=addition_x;
            }else{
            }
        }
    }
    mouse_x++;
    if(mouse_x>ofGetWidth())mouse_x=0;
}

void LineBelt::mouseMoved(int x, int y){
    this->mouse_x = x;
}

void LineBelt::draw_belt(){
    int index = SingleUserManager::user_agent.size();
    ofFill();
    for(int i = 0;i<line_num;i++){
        ofSetColor(color.at(i));
        if(this->mouse_x == (int)position.at(i) && index!=0){//mouseXとおなじX座標の線があれば
            FontManager::mbigfont.drawString("pos index: "+ofToString(i),position.at(i)-10,pos_center_y-line_length-18-100);
            FontManager::mbigfont.drawString(SingleUserManager::user_agent.at(i%index)->get_user_name(),position.at(i)-10,pos_center_y-line_length-100);
            FontManager::mbigfont.drawString(SingleUserManager::user_agent.at(i%index)->get_user_id(),position.at(i)-10,pos_center_y-line_length-100+18);
            FontManager::mbigfont.drawString("friends: "+ofToString(SingleUserManager::user_agent.at(i%index)->get_user_friends()),position.at(i)-10,pos_center_y-line_length-100+36);
            FontManager::mbigfont.drawString("statuses: "+ofToString(SingleUserManager::user_agent.at(i%index)->get_user_statuses()),position.at(i)-10,pos_center_y-line_length-100+54);
            FontManager::mbigfont.drawString(SingleUserManager::user_agent.at(i%index)->get_user_text(),position.at(i)-10,pos_center_y-line_length+72-100);
            ofRect(position.at(i)-5, pos_center_y-line_length, 10, line_length*2);
            break;
        }else{
            ofLine(position.at(i), pos_center_y-line_length/2, position.at(i), pos_center_y+line_length/2);
        }
    }
    ofSetColor(255);
}