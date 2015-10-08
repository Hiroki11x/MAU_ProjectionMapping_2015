//
//  TwitterRain.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/08.
//
//
#ifndef TwitterRain_h
#define TwitterRain_h

#include "ofMain.h"
#include "SceneElement.h"

#include "ofx3DFont.h"

class TwitterRain : public SceneElement {
public:
    
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    ofx3DFont font;
};
#endif
