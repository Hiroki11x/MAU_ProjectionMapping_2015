//
//  UsersManager.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/30.
//
//

#include "UserAgentsSceneManager.h"

void UsersAgentsSceneManager::setup(){
    elements.push_back(new UserAgents());
    elements.at(0)->init();
}

void UsersAgentsSceneManager::onMouseDown(int x, int y){}