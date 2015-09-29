//
//  IntroductionManager.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//

#include "IntroductionManager.h"

void IntroductionManager::setup(){
    elementIndex = 0;
    elements.push_back(new Loading(2.0,"Loading Tweets..."));
    elements.push_back(new Loading(2.0,"Loading Tweets..."));
    elements.push_back(new Loading(2.0,"Loading Tweets..."));
}

void IntroductionManager::update(){
    elements.at(elementIndex)->update();
}

void IntroductionManager::draw(){
    elements.at(elementIndex)->draw();
}

/*bool IntroductionManager::nextElement(){
    
}*/