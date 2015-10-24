//
//  FinalVideoSceneManager.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#include "FinalVideoSceneManager.h"

void FinalVideoSceneManager::setup(){
    //    elements.push_back(new AgentAnalyze());
    //    elements.back()->init();
}
void FinalVideoSceneManager::reset(){
    elements.at(0)->reset();
}

void FinalVideoSceneManager::onMouseDown(int x, int y){
    elements.at(0)->onMouseDown(x, y);
}

void FinalVideoSceneManager::keyPressed(int key){
    elements.at(0)->keyPressed(key);
}