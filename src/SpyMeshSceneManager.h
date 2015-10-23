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
#include "SpyMeshIntro.h"
#include "TwitterRain.h"
#include "ArtSpyDeforming.h"
#include "IconStream.h"
#include "StringNetwork.h"
#include "GlidShoot.h"
#include "WaveFractal.h"
#include "GlassBreak.h"
#include "LineFractal.h"
#include "EndingVideo.h"
#include "StartVideo.h"

class SpyMeshSceneManager:public SceneManager {
public:
    virtual void setup() override;
    virtual bool nextElement() override;
    virtual void keyPressed(int key) override;
    virtual void draw() override;
    
    bool splitView = false;
};
#endif