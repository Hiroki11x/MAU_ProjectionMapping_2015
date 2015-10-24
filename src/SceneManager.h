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
#include "SoundManager.h"

class SceneManager{
public:
    int elementIndex = 0;
    vector<SceneElement *> elements;
        
    virtual void setup(){
        //InitElements
    };
    virtual void update(){
        elements.at(elementIndex)->update();
    };
    virtual void draw(){
        ofSetWindowTitle("FPS:" + ofToString(ofGetFrameRate()));
        elements.at(elementIndex)->draw();
    };
    virtual void onMouseDown(int x,int y){
        elements.at(elementIndex)->onMouseDown(x, y);
    };
    virtual void keyPressed(int key){
        elements.at(elementIndex)->keyPressed(key);
    };
    
    virtual bool nextElement(){
        //SoundManager::stop();
        elements[elementIndex]->end();
        elementIndex++;
        if(elementIndex >= elements.size()){
            return false;
        }else{
            elements[elementIndex]->init();
            return true;
        }
    };
};
#endif 