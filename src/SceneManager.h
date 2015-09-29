//
//  SceneController.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//

#ifndef SceneManager_h
#define SceneManager_h
#include "ofMain.h"
#include "SceneElement.h"

class SceneManager{
public:
    int elementIndex = 0;
    vector<SceneElement *> elements;
        
    virtual void setup(){
        //InitElements
    };
    virtual void update(){};
    virtual void draw(){};
    
    bool nextElement(){
        elementIndex++;
        if(elementIndex >= elements.size()){
            return false;
        }else{
            return true;
        }
    };
};
#endif 