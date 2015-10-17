//
//  EffectScene.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/18.
//
//

#ifndef EffectScene_h
#define EffectScene_h

#include "ofMain.h"
#include "SceneElement.h"

class EffectScene : public SceneElement{

    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    void nextEffect();
};
#endif
