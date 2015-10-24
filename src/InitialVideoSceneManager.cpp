//
//  InitialVideoSceneManager.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#include "InitialVideoSceneManager.h"

void InitialVideoSceneManager::setup(){
    //    elements.push_back(new AgentAnalyze());
    //    elements.back()->init();
}
void InitialVideoSceneManager::reset(){
    elements.at(0)->reset();
}

void InitialVideoSceneManager::onMouseDown(int x, int y){
    elements.at(0)->onMouseDown(x, y);
}

void InitialVideoSceneManager::keyPressed(int key){
    elements.at(0)->keyPressed(key);
}