//
//  SpyMeshSceneManager.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#include "SpyMeshSceneManager.h"

void SpyMeshSceneManager::setup(){
    elements.push_back(new SpyMeshIntro());
    elements.push_back(new SpyMesh());
    elements.at(0)->init();
}

void SpyMeshSceneManager::onMouseDown(int x,int y){
    elements.at(elementIndex)->onMouseDown(x, y);
}