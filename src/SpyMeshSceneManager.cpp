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
    elements.push_back(new SpyMeshIntro());
    elements.push_back(new SpyMesh());
    elements.at(0)->init();
}