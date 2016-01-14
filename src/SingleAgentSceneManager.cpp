//
//  SingleAgentSceneManager.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/12.
//
//

#include "SingleAgentSceneManager.h"

void SingleAgentSceneManager::setup(){
//    elements.push_back(new SingleAgentAnalyze());
//    elements.back()->init();
}

void SingleAgentSceneManager::reset(){
    elements.at(0)->reset();
}

void SingleAgentSceneManager::onMouseDown(int x, int y){
    elements.at(0)->onMouseDown(x, y);
}

void SingleAgentSceneManager::keyPressed(int key){
    elements.at(0)->keyPressed(key);
}