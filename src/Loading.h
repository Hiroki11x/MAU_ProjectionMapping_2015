//
//  Loading.h
//  MauInteractive
//
//  Created by SakuragiYoshimasa on 2015/09/25.
//
//
#ifndef MauInteractive_Loading_h
#define MauInteractive_Loading_h
#include "ofMain.h"
#include "SceneElement.h"

class Loading : public SceneElement {
public:
    float interval;
    float barLength;
    float wait;
    bool writeText;
    string text;
    ofTrueTypeFont drawer;
    
    virtual void draw() override;
    virtual void update() override;
    
    Loading(){
        
        drawer.loadFont("Arial.ttf",30,false);
        this->interval = 2.0;
        this->text = "Loading Tweets...";
        this->barLength = 0;
        this->wait = 0;
        this->writeText = true;
        cout << "load init" << endl;
    };
};
#endif