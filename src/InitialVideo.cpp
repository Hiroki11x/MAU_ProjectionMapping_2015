//
//  InitialVideo.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#include "InitialVideo.h"


void InitialVideo::reset(){
    
}

void InitialVideo::check_is_json_new(){
    int add_num;
    if(SingleUserManager::json_num<JsonReceiver::getInstance().getUsersInfo().size()){
        add_num = JsonReceiver::getInstance().getUsersInfo().size() - SingleUserManager::json_num;
        addAgent(add_num);
        ofxSuperLogUtil::set_log("add agent","add "+ofToString(add_num)+" agents");
    }
}

void InitialVideo::addAgent(int add_num){
    for(int i=0;i<add_num;i++){
        SingleUserManager::json_num++;//json_numはここで
    }
}

void InitialVideo::update(){
    if(isMovieOpen){
        if(video.isPlaying())video.update();
    }
    check_is_json_new();
}

void InitialVideo::draw(){
    ofSetColor(255);
    if(isMovieOpen){
        if(video.isPlaying()){
            video.draw(0, 0, ofGetWidth(), ofGetHeight());
        }else if(img.bAllocated()){
            img.draw(0, 0, ofGetWidth(), ofGetHeight());
        }
    }
}

void InitialVideo::init(){
    video.loadMovie("comp1_1.mp4");
    video.setLoopState(OF_LOOP_NONE);
    img.loadImage("pleasewait.png");
    isMovieOpen = true;
}

void InitialVideo::end(){
    
}

void InitialVideo::onMouseDown(int x,int y){
    
}

void InitialVideo::keyPressed(int key){
    if (key == OF_KEY_RETURN) {
        if(video.isLoaded())video.play();
    }else if(key == OF_KEY_TAB){//Loadingは止めとく
        video.stop();
        isMovieOpen = false;
        video.setPaused(true);
        video.closeMovie();
        img.clear();
    }
}