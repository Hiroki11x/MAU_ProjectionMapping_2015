//
//  IntroductionManager.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
#include "IntroductionManager.h"

void IntroductionManager::setup(){
    elements.push_back(new BuildPC());
    elements.push_back(new Loading());
    elements.push_back(new Loading());
}

void IntroductionManager::update(){
    elements.at(elementIndex)->update();
}

void IntroductionManager::draw(){
    elements.at(elementIndex)->draw();
}