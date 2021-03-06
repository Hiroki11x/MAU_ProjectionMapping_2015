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
    virtual void reset(){
        elements.at(elementIndex)->reset();
    };
    virtual void update(){
        elements.at(elementIndex)->update();
    };
    virtual void draw(){
         elements.at(elementIndex)->draw();
    };
    virtual void onMouseDown(int x,int y){};
    virtual void keyPressed(int key){};
    
    virtual bool nextElement(){
        elements[elementIndex]->end();
        elementIndex++;
        if(elementIndex >= elements.size()){
            elementIndex = 0;
            return true;
        }else{
            elements[elementIndex]->init();
            return true;
        }
    };
};
#endif 