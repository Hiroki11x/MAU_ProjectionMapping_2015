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
//    mode = (mode+1)%2;
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
            break;
        case 1:
            draw_bezier_map(num);
            break;
        default:
            break;
    }
}

void ShiseidoLifeClock::draw_bezier_map(int num){
    
    update(num);//数とかを更新
    
    ofNoFill();
    ofPushMatrix();
    ofTranslate(2*ofGetWidth()/3, ofGetHeight()/2);
    
    
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
//        if(i == vec.size()-1){
//            ofSetColor(255);
//            JsonReceiver::usersInfo.back().icon.drawSubsection(vec.at(index3).x*1.1-25, vec.at(index3).y*1.1-25,50,50,2,2);
//        }
    }
    
    ofPopMatrix();
}
