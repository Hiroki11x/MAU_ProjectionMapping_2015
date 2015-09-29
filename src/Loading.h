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
    string text;
    float barLength;
    float wait;
    bool writeText;

    virtual void draw() override;
    virtual void update() override;
    ofTrueTypeFont drawer;
    
    Loading(){
        
        drawer.loadFont("Arial.ttf",30,false);
        this->interval = 2.0;
        this->text = "Loading Tweets...";
        this->barLength = 0;
        this->wait = 0;
        this->writeText = true;
        cout << "load init" << endl;
    };
    //~Loading(){};
    
};
#endif