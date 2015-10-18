//
//  WaveFractal.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/19.
//
//

#ifndef WaveFractal_h
#define WaveFractal_h

#include "ofMain.h"
#include "SceneElement.h"

class WaveFractal : public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    virtual void stop() override;
};

#endif
