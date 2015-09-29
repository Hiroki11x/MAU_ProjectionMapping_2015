//
//  Fadeout.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//

#ifndef Fadeout_h
#define Fadeout_h

#include "ofMain.h"
#include "SceneElement.h"

class Fadeout: public SceneElement {
public:
    float fadeTime;
    float waitTime;
    
    Fadeout(){
        this->fadeTime = 300;
        this->waitTime = 0;
    };
    
    virtual void draw() override;
    virtual void update() override;
};
#endif /* Fadeout_hpp */
