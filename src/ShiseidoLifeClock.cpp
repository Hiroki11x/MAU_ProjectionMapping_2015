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

void ShiseidoLifeClock::reset(){
    userNames.clear();
}

void ShiseidoLifeClock::switch_mode(){//使わない
    mode = (mode+1)%5;
    userNames.clear();
}

void ShiseidoLifeClock::init(){
    start_time = ofGetElapsedTimef();
    json_num =0;
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
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
    ofDrawBitmapString("Mode:"+ofToString(mode), ofGetWidth()-100,30);
    switch (mode) {
        case 0:
            draw_bezier_web(num);
            break;
        case 1:
            draw_bezier_map(num);
            break;
        case 2:
            draw_mesh(num);
            break;
        case 3:
            draw_default_circle();
            break;
        break;case 4:
            draw_bezier_circle(num);
            break;
        default:
            break;
    }
}

void ShiseidoLifeClock::draw_mesh(int num){//Meshのとこ
    update(num);
    ofNoFill();
    mesh.clearVertices();
    mesh.clearColors();

    
    int index1,index2,index3;
    ofPushMatrix();
    ofTranslate(3*ofGetWidth()/5, ofGetHeight()/2);
//    cam.begin();
    for(int i = 0;i<vec.size();i++){
        index1 = pow(ofSignedNoise(i,ofGetFrameNum()/1000),2)*vec.size();
        index3 = pow(ofSignedNoise(i,ofGetElapsedTimef()/1000),2)*vec.size();
        
        mesh.addColor(ofFloatColor(0.6,0.6,0.6,0.6));
        mesh.addVertex(vec.at(index1)*0.7);
        
        mesh.addColor(ofFloatColor(0.4,0.4,0.4,0.4));
        mesh.addVertex(vec.at(index3)*1.25);
        
        
        mesh.addColor(ofFloatColor(0.4,0.4,0.4,0.4));
        mesh.addVertex(vec.at(i)*1.5);
        
        ofSetColor(170,120);
        ofCircle(vec.at(index1)*0.7,3);
        ofCircle(vec.at(index3)*1.5,3);
        ofCircle(vec.at(index3)*1.25,3);
        
        if(i<SingleUserManager::user_agent.size()){
            ofSetColor(ofColor::fromHsb(255*pow(ofSignedNoise(i,ofGetFrameNum()/10000),2),150,200),170);
            FontManager::mfont.drawString(SingleUserManager::user_agent.at(i)->get_user_name(), vec.at(index3).x*1.5,vec.at(index3).y*1.5);
        }
    }
    
    mesh.draw();
//    cam.end();
//    cam.setPosition(ofVec3f(0,0,200*(1.5+sin(ofGetElapsedTimef()))));
//    cam.lookAt(mesh.getVertices().at(index1));
    ofPopMatrix();

}

void ShiseidoLifeClock::draw_bezier_web(int num){//白黒大きくなるやつ
    update(num);//数とかを更新
    ofSetLineWidth(0.01);
    ofNoFill();
    ofPushMatrix();
    ofTranslate(3*ofGetWidth()/5, ofGetHeight()/2);
    int index1,index3;
    float tempAngle;
    ofVec2f tempVec;
    for(int i = 0;i<vec.size();i++){
        ofSetColor(ofColor::fromHsb(300,0, pow(ofSignedNoise(i,ofGetFrameNum()/10000),2)*255+50),150);
        index1 = pow(ofSignedNoise(i,ofGetFrameNum()/1000),2)*vec.size();
        index3 = pow(ofSignedNoise(i,ofGetElapsedTimef()/1000),2)*vec.size();
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


void ShiseidoLifeClock::draw_bezier_map(int num){//一番それっぽいやつ
    
    update(num);//数とかを更新
    ofSetLineWidth(0.05);
    ofNoFill();
    ofPushMatrix();
    ofTranslate(3*ofGetWidth()/5, ofGetHeight()/2);
    
    int index1,index2,index3;
    for(int i = 0;i<vec.size();i++){
        ofSetColor(ofColor::fromHsb((ofMap(i, 0, vec.size(), 0, 255)), 200, 200),150);
        index1 = pow(ofSignedNoise(i,ofGetFrameNum()/1000),2)*vec.size();
        index3 = pow(ofSignedNoise(i,ofGetElapsedTimef()/100),2)*vec.size();
        ofBezier(vec.at(index1).x,vec.at(index1).y,
                 vec.at(index1).x/4,vec.at(index1).y/4,
                 vec.at(index3).x/4,vec.at(index3).y/4,
                 vec.at(index3).x,vec.at(index3).y);
        
        ofCircle(vec.at(index3)*1.01,3);
    }
    ofPopMatrix();
}

void ShiseidoLifeClock::draw_default_circle(){//波みたいなやつ
    ofVec2f basis_vec;//大きい全体のベクトル
    ofVec2f inner_vec;//Bezier用の中間点ベクトル
    int angle;
    int hue;
    
    ofSetLineWidth(0.1);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    for(int i =0;i<ofGetElapsedTimef()*10;i+=1){
        angle = i;
        
        inner_vec = ofVec2f(
                            cos(ofSignedNoise(ofGetFrameNum()/1000.0,i,i)*2*PI),
                            sin(ofSignedNoise(ofGetFrameNum()/1000.0,i,i)*2*PI)
                            );
        inner_vec *= 50;
        
        basis_vec = ofVec2f(
                            cos(angle/180.0*PI),
                            sin(angle/180.0*PI)
                            );
        basis_vec *= 300;
        
        hue = ofMap(i, 0, 360, 0, 255);
        ofSetColor(ofColor::fromHsb(hue, 170, 200),170);
        ofNoFill();
        
        ofBezier(0, 0,
                 6*inner_vec.y,6*inner_vec.x,
                 6*inner_vec.x,6*inner_vec.y,
                 basis_vec.x, basis_vec.y);
        ofFill();
        ofCircle(basis_vec.x*1.01, basis_vec.y*1.01, 1);
    }
    ofPopMatrix();
}

void ShiseidoLifeClock::draw_bezier_circle(int num){
    ofVec2f basis_vec;//大きい全体のベクトル
    ofVec2f inner_vec;//Bezier用の中間点ベクトル
    int angle;
    int hue;
    
    ofSetLineWidth(0.1);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

    ofPopMatrix();
}
