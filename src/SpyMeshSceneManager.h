//
//  SpyMeshSceneManager.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//

#ifndef SpyMeshSceneManager_h
#define SpyMeshSceneManager_h

#include "ofMain.h"
#include "SceneManager.h"
#include "SceneElement.h"
#include "SpyMesh.h"

class SpyMeshSceneManager:public SceneManager {
public:
    
    virtual void setup() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void onMouseDown(int x,int y) override;
};

#endif /* SpyMeshSceneManager_hpp */
