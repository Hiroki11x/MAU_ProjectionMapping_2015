//
//  Scene.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#ifndef SceneElement_h
#define SceneElement_h

#include "ofMain.h"
#include "SoundManager.h"

class SceneElement {
public:
    virtual void update(){};
    virtual void draw(){};
    virtual void init(){};
    virtual void stop(){};
    virtual void end(){};
    virtual void onMouseDown(int x,int y){};
    virtual void keyPressed(int key){};
};
#endif