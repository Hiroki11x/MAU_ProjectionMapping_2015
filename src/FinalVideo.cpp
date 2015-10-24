//
//  FinalVideo.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#include "FinalVideo.h"

void FinalVideo::reset(){
    
}

void FinalVideo::update(){
    if(video.isPlaying())video.update();
    
}

void FinalVideo::draw(){
    ofSetColor(255);
    if(video.isPlaying()){
       video.draw(0, 0, ofGetWidth(), ofGetHeight());
    }else{
        ofBackground(0);
    }
}

void FinalVideo::init(){
    video.loadMovie("end.mp4");
    video.setLoopState(OF_LOOP_NONE);
}

void FinalVideo::end(){
    
}

void FinalVideo::onMouseDown(int x,int y){
    
}

void FinalVideo::keyPressed(int key){
    if (key == OF_KEY_RETURN) {
        video.play();
    }else if(key == OF_KEY_TAB){
        video.stop();
    }
}