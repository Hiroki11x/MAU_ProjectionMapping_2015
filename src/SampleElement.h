//
//  SampleElement.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/13.
//
//
#ifndef SampleElement_h
#define SampleElement_h

#include "ofMain.h"
#include "SceneElement.h"

class SampleElemtnt : public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
};
#endif
