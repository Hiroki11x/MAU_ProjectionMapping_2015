//
//  LoadingVideoSceneManager.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#include "LoadingVideoSceneManager.h"

void LoadingVideoSceneManager::setup(){
    //    elements.push_back(new AgentAnalyze());
    //    elements.back()->init();
}
void LoadingVideoSceneManager::reset(){
    elements.at(0)->reset();
}

void LoadingVideoSceneManager::onMouseDown(int x, int y){
    elements.at(0)->onMouseDown(x, y);
}

void LoadingVideoSceneManager::keyPressed(int key){
    elements.at(0)->keyPressed(key);
}