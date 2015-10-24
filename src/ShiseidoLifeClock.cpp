//
//  ShiseidoLifeClock.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/12.
//
//

#include "ShiseidoLifeClock.h"



float ShiseidoLifeClock::start_time;
int ShiseidoLifeClock::json_num;

void ShiseidoLifeClock::add_line_num(int add){//新たに追加していくやつ
    line_num+=add;
    for(int i = 0;i< add ;i++){
        vec.push_back(ofVec2f());
        vec.back() = ofVec2f(cos(ofSignedNoise(ofGetFrameNum()/3000.0,i)*2*PI),
                             sin(ofSignedNoise(ofGetFrameNum()/3000.0,i)*2*PI));
        vec.at(i)*= 300;
    }
}

void ShiseidoLifeClock::reset(){
    userNames.clear();
    vec.clear();
    init();
    line_num =vec.size();
}

void ShiseidoLifeClock::set_line_num(int num){
    line_num = num;
}

int ShiseidoLifeClock::switch_mode(){//使わない
    mode = (mode+1)%3+1;
    userNames.clear();
    return mode;
}

void ShiseidoLifeClock::init(){
    start_time = ofGetElapsedTimef();
    json_num =0;
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    ofSetLineWidth(2);
    vec.clear();
    for(int i = 0;i< 2 ;i++){
        vec.push_back(ofVec2f());
        vec.back() = ofVec2f(cos(ofSignedNoise(ofGetFrameNum()/1000.0,i,i)*2*PI),
                             sin(ofSignedNoise(ofGetFrameNum()/1000.0,i,i)*2*PI));
    }
}


void ShiseidoLifeClock::update(){
    
    for(int i = 0;i< vec.size() ;i++){
        vec.at(i) = ofVec2f(cos(ofSignedNoise(ofGetFrameNum()/3000.0,i)*2*PI),
                            sin(ofSignedNoise(ofGetFrameNum()/3000.0,i)*2*PI));
        vec.at(i)*= 300;
    }
}

void ShiseidoLifeClock::draw(){
    ofDrawBitmapString("Mode:"+ofToString(mode), ofGetWidth()-100,30);
    switch (mode) {
        case 0:
            draw_bezier_web();
            break;
        case 1:
            draw_bezier_map();//一番それっぽいやつ
            break;
        case 2:
            draw_mesh();//Meshのやつ
            break;
        case 3:
            draw_default_circle();//波みたいなやつの半円
            break;
        break;case 4:
            draw_bezier_circle();
            break;
        default:
            break;
    }
}

void ShiseidoLifeClock::draw_mesh(){//[2]Meshのとこ(Json同期)
    update();
    ofNoFill();
    mesh.clearVertices();
    mesh.clearColors();

    ofSetLineWidth(1);
    int index1,index2,index3;
    ofPushMatrix();
    ofTranslate(3*ofGetWidth()/5, ofGetHeight()/2);
    for(int i = 0;i<vec.size()/2;i++){
        index1 = pow(ofSignedNoise(i,ofGetFrameNum()/1000),2)*vec.size();
        index3 = pow(ofSignedNoise(i,ofGetElapsedTimef()/1000),2)*vec.size();
        
        mesh.addColor(ofFloatColor(0.7,0.7,0.7,0.7));
        mesh.addVertex(vec.at(index3)*1.1);
        
        mesh.addColor(ofFloatColor(0.5,0.5,0.5,0.5));
        mesh.addVertex(vec.at(i)*1.3);
        
        mesh.addColor(ofFloatColor(0.7,0.7,0.7,0.7));
        mesh.addVertex(vec.at(index1)*0.5);
        
        ofSetColor(170,240);
        ofCircle(vec.at(index1)*0.5,3);
        ofCircle(vec.at(index3)*1.3,3);
        ofCircle(vec.at(i)*1.1,3);
        ofLine(ofVec2f(cos(i),sin(i))*1.34*300,ofVec2f(cos(i),sin(i))*1.38*300);
        if(i<SingleUserManager::user_agent.size()){
            ofSetColor(ofColor::fromHsb(255*pow(ofSignedNoise(i,ofGetFrameNum()/10000),2),250,240),255);
            FontManager::mbigfont.drawString(SingleUserManager::user_agent.at(i)->get_user_id(), vec.at(i).x*1.1,vec.at(i).y*1.1);
            FontManager::mbigfont.drawString(SingleUserManager::user_agent.at(i)->get_user_name(), vec.at(index3).x*1.3,vec.at(index3).y*1.3);
        }
    }
    mesh.draw();
    ofPopMatrix();
}

void ShiseidoLifeClock::draw_bezier_web(){//白黒大きくなるやつ
}


void ShiseidoLifeClock::draw_bezier_map(){//[1]一番それっぽいやつ(Json同期)
    update();//数とかを更新
    ofSetLineWidth(2);
    ofNoFill();
    ofPushMatrix();
    ofTranslate(3*ofGetWidth()/5, ofGetHeight()/2);
    int index1,index2,index3;
    for(int i = 0;i<vec.size();i++){
        ofSetColor(ofColor::fromHsb((ofMap(i, 0, vec.size(), 0, 255)), 250, 240),205);
        index1 = pow(ofSignedNoise(i,ofGetFrameNum()/1000),2)*vec.size();
        index3 = pow(ofSignedNoise(i,ofGetElapsedTimef()/100),2)*vec.size();
        ofBezier(vec.at(index1).x,vec.at(index1).y,
                 vec.at(index1).x/4,vec.at(index1).y/4,
                 vec.at(index3).x/4,vec.at(index3).y/4,
                 vec.at(index3).x*1.3,vec.at(index3).y*1.3);
        if(i<SingleUserManager::user_agent.size()){
            glPushMatrix();
            glRotatef(ofVec2f(1,0).angle(vec.at(index3)), 0, 0, 1);
            FontManager::mbigfont.drawString(SingleUserManager::user_agent.at(i)->get_user_id(), vec.at(index3).length()*1.3,0);
            glPopMatrix();
        }
        ofLine(ofVec2f(cos(i),sin(i))*1.3*300,ofVec2f(cos(i),sin(i))*1.34*300);
        ofLine(ofVec2f(cos(i*0.5),sin(i*0.5))*1.3*150,ofVec2f(cos(i*0.5),sin(i*0.5))*1.34*150);
    }
    ofPopMatrix();
}

void ShiseidoLifeClock::draw_default_circle(){//[3]波みたいなやつの半円(Json同期)
    ofVec2f basis_vec;//大きい全体のベクトル
    ofVec2f inner_vec;//Bezier用の中間点ベクトル
    float angle;
    int hue;
    
    ofSetLineWidth(2);
    ofPushMatrix();
    ofTranslate(50, ofGetHeight()/2);
    ofRotateZ(-90);
    
    for(int i =0;i<line_num%180;i+=1){
        angle = i*2;
        inner_vec = ofVec2f(cos(ofSignedNoise(ofGetFrameNum()/1000.0,i,i)*2*PI),
                            sin(ofSignedNoise(ofGetFrameNum()/1000.0,i,i)*2*PI));
        inner_vec *= 50;
        basis_vec = ofVec2f(cos(angle/180.0*PI),
                            sin(angle/180.0*PI));
        basis_vec *= 300;
        hue = ofMap(i, 0, 90, 0, 255);
        ofSetColor(ofColor::fromHsb(hue, 170, 200),255);
        ofNoFill();
        
        ofBezier(0, 0,
                 6*inner_vec.y,6*inner_vec.x,
                 8*inner_vec.x,8*inner_vec.y,
                 basis_vec.x*1.3, basis_vec.y*1.3);
        ofFill();
        ofLine(basis_vec*1.32,basis_vec*1.36);
        if(i<SingleUserManager::user_agent.size()){
            glPushMatrix();
            glRotatef(angle, 0, 0, 1);
            FontManager::mbigfont.drawString(SingleUserManager::user_agent.at(i)->get_user_id(), basis_vec.length()*1.36,0);
            glPopMatrix();
        }
    }
    ofPopMatrix();
}

void ShiseidoLifeClock::draw_bezier_circle(){
}
