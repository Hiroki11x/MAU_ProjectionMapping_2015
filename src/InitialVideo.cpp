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

void InitialVideo::update(){

    if(video.isPlaying())video.update();
    
}

void InitialVideo::draw(){
    ofSetColor(255);
    if(video.isPlaying()){
        video.draw(0, 0, ofGetWidth(), ofGetHeight());
    }else{
        img.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
}

void InitialVideo::init(){
    video.loadMovie("comp1_1.mp4");
    video.setLoopState(OF_LOOP_NONE);
    img.loadImage("pleasewait.png");
}

void InitialVideo::end(){
    
}

void InitialVideo::onMouseDown(int x,int y){
    
}

void InitialVideo::keyPressed(int key){
    if (key == OF_KEY_RETURN) {
        video.play();
    }else if(key == OF_KEY_TAB){
        video.stop();
        video.firstFrame();
    }
}