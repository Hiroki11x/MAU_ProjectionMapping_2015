//
//  AgentAnalyzeSceneManager.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/09.
//
//

#include "AgentAnalyzeSceneManager.h"

void AgentAnalyzeSceneManager::setup(){
    elements.push_back(new AgentAnalyze());
    elements.back()->init();
}

void AgentAnalyzeSceneManager::onMouseDown(int x, int y){
    elements.at(0)->onMouseDown(x, y);
}

void AgentAnalyzeSceneManager::keyPressed(int key){
    elements.at(0)->keyPressed(key);
}