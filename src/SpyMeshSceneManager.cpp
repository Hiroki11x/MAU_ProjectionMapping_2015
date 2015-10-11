//
//  SpyMeshSceneManager.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#include "SpyMeshSceneManager.h"

void SpyMeshSceneManager::setup(){
    SoundManager::init();
    elements.push_back(new ArtSpyDeforming());
    elements.push_back(new TwitterRain());
    elements.push_back(new SpyMeshIntro());
    elements.push_back(new SpyMesh());
    elements.push_back(new IconStream());
    for(int i = 0; i < elements.size(); i++){
        elements.at(i)->init();
    }
}

bool SpyMeshSceneManager::nextElement(){

     elements[elementIndex]->end();
     elementIndex++;
     if(elementIndex >= elements.size()){
         elementIndex = 0;
     }
    return true;
}

void SpyMeshSceneManager::draw(){

    ofSetWindowTitle("FPS:" + ofToString(ofGetFrameRate()));
    if(!splitView){
        elements.at(elementIndex)->draw();
    }else{
        glViewport(0, 0, ofGetWidth()/2, ofGetHeight()/2);
        elements.at(elementIndex)->draw();
    
        glViewport(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight()/2);
        elements.at(elementIndex)->draw();
        
        glViewport(0, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);
        elements.at(elementIndex)->draw();
        
        glViewport(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);
        elements.at(elementIndex)->draw();
    }
}

void SpyMeshSceneManager::keyPressed(int key){
    
    switch (key) {
        case '1':
            elementIndex = 0;
            return;
        case '2':
            elementIndex = 1;
            return;
        case '3':
            elementIndex = 2;
            return;
        case '4':
            elementIndex = 3;
            return;
        case '5':
            elementIndex = 4;
            return;
        case '6':
            splitView = !splitView;
            return;
    }
    elements.at(elementIndex)->keyPressed(key);
};
