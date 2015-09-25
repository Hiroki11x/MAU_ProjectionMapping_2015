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

class Loading {
    
public:
    float interval;
    string text;
    float barLength;
    float wait;
    bool writeText;

    void draw();
    
    Loading(float interval,string text){
        this->interval = interval;
        this->text = text;
        this->barLength = 0;
        this->wait = 0;
        this->writeText = true;
    };
    //~Loading(){};
    
};
#endif