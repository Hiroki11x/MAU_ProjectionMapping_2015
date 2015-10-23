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
}

void EndingVideo::update(){

    if(!vPlayer.isPlaying()){
        vPlayer.play();
    }
    
    vPlayer.update();
    
}

void EndingVideo::draw(){
    ofDisableBlendMode();
    ofDisableDepthTest();
    ofDisableAlphaBlending();
    vPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void EndingVideo::onMouseDown(int x, int y){}

void EndingVideo::keyPressed(int key){
    
}

void EndingVideo::stop(){
    vPlayer.stop();
}

