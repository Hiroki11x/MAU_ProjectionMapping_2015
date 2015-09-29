//
//  textExplosion.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//

#ifndef textExplosion_h
#define textExplosion_h

#include "ofMain.h"
#include "SceneElement.h"

class textExplosion : public SceneElement {
public:
    
    string text;
    ofTrueTypeFont drawer;
    int drawFrame;
    int waitFrame;
    
    textExplosion(){
        this->text = "";
        this->drawer.loadFont("Arial.ttf", 20);
        this->drawFrame = 600;
        this->waitFrame = 0;
    };
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    
};
#endif /* textExplosion_hpp */
