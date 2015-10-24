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
    elements.push_back(new LoadingVideo());
    elements.push_back(new InitialVideo());
    elements.push_back(new FinalVideo());
    for(int i = 0; i < elements.size(); i++){
        elements.at(i)->init();
    }
}

bool UserAgentsSceneManager::nextElement(){//スペースでの繊維用
    elements[elementIndex]->end();
    elementIndex++;
    if(elementIndex >= elements.size()){
        elementIndex = 0;
    }
    //elements.at(elementIndex)->reset();
    return true;
}

void UserAgentsSceneManager::keyPressed(int key){
    switch (key) {
        case '1':
            elementIndex = 0;//UserAgent
            //elements.at(elementIndex)->reset();
            return;
        case '2':
            elementIndex = 1;//AgentAnalyza
            //elements.at(elementIndex)->reset();
            return;
        case '3':
            elementIndex = 2;//SingleAnalyze
            //elements.at(elementIndex)->reset();
            return;
        case '4':
            elementIndex = 3;//SingleAnalyze
            //elements.at(elementIndex)->reset();
            return;
        case '5':
            elementIndex = 4;//SingleAnalyze
            //elements.at(elementIndex)->reset();
            return;
        case '6':
            elementIndex = 5;//SingleAnalyze
            //elements.at(elementIndex)->reset();
            return;
    }
    elements.at(elementIndex)->keyPressed(key);
}

void UserAgentsSceneManager::onMouseDown(int x, int y){
    elements.at(0)->onMouseDown(x, y);
}

void UserAgentsSceneManager::draw(){
    elements.at(elementIndex)->draw();
}