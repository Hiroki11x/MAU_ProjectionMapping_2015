//
//  EndingVideo.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/23.
//
//

#include "EndingVideo.h"

void EndingVideo::init(){
    vPlayer.loadMovie("ending.mp4");
    vPlayer.setLoopState(OF_LOOP_NONE);
}

void EndingVideo::update(){

   if(vPlayer.isPlaying()){
    
       vPlayer.update();
    }
}

void EndingVideo::draw(){
    
    ofSetColor(255);
    ofDisableBlendMode();
    ofDisableDepthTest();
    ofDisableAlphaBlending();
    if(vPlayer.isPlaying()){
        vPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
    }else{
        ofBackground(0);
    }
}

void EndingVideo::onMouseDown(int x, int y){}

void EndingVideo::keyPressed(int key){
    if(key == OF_KEY_RETURN){
        isPlaying = !isPlaying;
        if(!isPlaying){
            vPlayer.stop();
        }else{
            vPlayer.play();
        }
    }
}

void EndingVideo::stop(){
    ofBackground(0);
    vPlayer.stop();
}

