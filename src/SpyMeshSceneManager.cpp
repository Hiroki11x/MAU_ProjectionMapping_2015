//
//  SpyMeshSceneManager.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#include "SpyMeshSceneManager.h"

void SpyMeshSceneManager::setup(){
    SoundManager::init();
    elements.push_back(new TwitterRain());
    elements.push_back(new SpyMeshIntro());
    elements.push_back(new SpyMesh());
    for(int i = 0; i < elements.size(); i++){
        elements.at(i)->init();
    }
}

bool SpyMeshSceneManager::nextElement(){
    
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

void SpyMeshSceneManager::keyPressed(int key){
    
    switch (key) {
        case '1':
            elementIndex = 0;
            return;
        case '2':
            elementIndex = 1;
            return;
        case '3':
            elementIndex = 2;
            return;
    }
    elements.at(elementIndex)->keyPressed(key);
};
