//
//  UsersManager.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/30.
//
//  userAgentSceneモードの時
//  //ElementsはUserAgentの集合体のUserAgents
//

#include "UserAgentsSceneManager.h"


void UserAgentsSceneManager::setup(){//ここでelementsにpushbackする順番がのちのキーに対応
    elements.push_back(new UserAgents());
    elements.push_back(new AgentAnalyze());
    elements.push_back(new SingleAgentAnalyze());
    for(int i = 0; i < elements.size(); i++){
        elements.at(i)->init();
    }
}

bool UserAgentsSceneManager::nextElement(){
    //SoundManager::stop();
    elements[elementIndex]->end();
    elementIndex++;
    if(elementIndex >= elements.size()){
        elementIndex = 0;
        return true;
    }else{
        //elements[elementIndex]->init();
        return true;
    }
}

void UserAgentsSceneManager::keyPressed(int key){
    switch (key) {
        case '1':
            elementIndex = 0;//UserAgent
            return;
        case '2':
            elementIndex = 1;//AgentAnalyza
            return;
        case '3':
            elementIndex = 2;//Loading
            return;
    }
    elements.at(elementIndex)->keyPressed(key);
}

void UserAgentsSceneManager::onMouseDown(int x, int y){
    elements.at(0)->onMouseDown(x, y);
}
