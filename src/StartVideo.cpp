//
//  StartVideo.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/24.
//
//

#include "StartVideo.h"

void StartVideo::init(){
    vPlayer.loadMovie("start.mp4");
    waitImage.loadImage("wait.png");
    vPlayer.setLoopState(OF_LOOP_NONE);
}

void StartVideo::update(){
    
    if(vPlayer.isPlaying()){
        vPlayer.update();
    }
}

void StartVideo::draw(){

    ofSetColor(255);
    if(vPlayer.isPlaying()){
        ofDisableBlendMode();
        ofDisableDepthTest();
        ofDisableAlphaBlending();
        vPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    if(!isStarted){
        ofDisableBlendMode();
        ofDisableDepthTest();
        ofDisableAlphaBlending();
        waitImage.draw(0, 0,ofGetWidth(),ofGetHeight());
    }
}

void StartVideo::onMouseDown(int x, int y){}

void StartVideo::keyPressed(int key){
    switch (key) {
        case OF_KEY_RETURN:
            isStarted = true;
            isPlaying = !isPlaying;
            if(!isPlaying){
                vPlayer.stop();
            }else{
                vPlayer.play();
            }
            break;
        default:
            break;
    }
}

void StartVideo::stop(){
    vPlayer.stop();
    //ofBackground(0);
}
