//
//  ShiseidoLifeClock.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/12.
//
//

#include "ShiseidoLifeClock.h"

float ShiseidoLifeClock::start_time;

void ShiseidoLifeClock::switch_mode(){//使わない
    mode = (mode+1)%2;
}

void ShiseidoLifeClock::init(){
    start_time = ofGetElapsedTimef();
    
    vec.clear();
    for(int i = 0;i< 200 ;i++){
        vec.push_back(ofVec2f());
        vec.back() = ofVec2f(
                             cos(ofSignedNoise(ofGetFrameNum()/1000.0,i,i)*2*PI),
                             sin(ofSignedNoise(ofGetFrameNum()/1000.0,i,i)*2*PI)
                             );
        
    }
}

void ShiseidoLifeClock::update(int num){
    max_angle = (ofGetElapsedTimef()-start_time)*10;
    if(max_angle>=360){
        init();
    }
    
    if (num>vec.size()) {//numの方が多かったらvecをpush_back
        while (num>vec.size()) {
            vec.push_back(ofVec2f());
        }
    }
    
    for(int i = 0;i< vec.size() ;i++){
        vec.at(i) = ofVec2f(
                            cos(ofSignedNoise(ofGetFrameNum()/3000.0,i)*2*PI),
                            sin(ofSignedNoise(ofGetFrameNum()/3000.0,i)*2*PI)
                            );
        vec.at(i)*= 300;
    }
}

void ShiseidoLifeClock::draw(int num){
    switch (mode) {
        case 0:
            draw_bezier_web(num);
            break;
        case 1:
            draw_bezier_map(num);
            break;
        case 2:
            draw_mesh(num);
        default:
            break;
    }
}

void ShiseidoLifeClock::draw_mesh(int num){
    ofMesh mesh;

}

void ShiseidoLifeClock::draw_bezier_web(int num){
    update(num);//数とかを更新
    ofSetLineWidth(0.05);
    ofNoFill();
    ofPushMatrix();
    ofTranslate(3*ofGetWidth()/5, ofGetHeight()/2);
    int index1,index3;
    float tempAngle;
    ofVec2f tempVec;
    for(int i = 0;i<vec.size();i++){
        ofSetColor(ofColor::fromHsb(300,0, pow(ofSignedNoise(i,ofGetFrameNum()/10000),2)*255+50));
        index1 = pow(ofSignedNoise(i,ofGetFrameNum()/10000),2)*vec.size();
        index3 = pow(ofSignedNoise(i,ofGetElapsedTimef()/10000),2)*vec.size();
        tempAngle = ofMap(i,0,vec.size(),0,2*PI);
        tempVec = ofVec2f(cos(tempAngle),sin(tempAngle))*(num*5+250);
        ofBezier(0,0,
                 vec.at(index1).x/2,vec.at(index1).y/2,
                 vec.at(index3).x,vec.at(index3).y,
                 tempVec.x,tempVec.y);
    }
    ofCircle(0,0,tempVec.length());
    ofPopMatrix();
}


void ShiseidoLifeClock::draw_bezier_map(int num){
    
    update(num);//数とかを更新
    ofSetLineWidth(0.05);
    ofNoFill();
    ofPushMatrix();
    ofTranslate(3*ofGetWidth()/5, ofGetHeight()/2);
    
    int index1,index2,index3;
    for(int i = 0;i<vec.size();i++){
        ofSetColor(ofColor::fromHsb((ofMap(i, 0, vec.size(), 0, 255)), 200, 200));
        index1 = pow(ofSignedNoise(i,ofGetFrameNum()/1000),2)*vec.size();
        index3 = pow(ofSignedNoise(i,ofGetElapsedTimef()/100),2)*vec.size();
        ofBezier(vec.at(index1).x,vec.at(index1).y,
                 vec.at(index1).x/4,vec.at(index1).y/4,
                 vec.at(index3).x/4,vec.at(index3).y/4,
                 vec.at(index3).x,vec.at(index3).y);
        
        ofCircle(vec.at(index3)*1.01,2);
    }
    ofPopMatrix();
}
