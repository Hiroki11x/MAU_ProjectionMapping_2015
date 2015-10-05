//
//  IntroductionManager.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
#include "IntroductionManager.h"

void IntroductionManager::setup(){
    elements.push_back(new BuildPC());
    //elements.push_back(new textExplosion());
    //elements.push_back(new Fadeout());
    elements.push_back(new Loading());
    elements.at(0)->init();
}