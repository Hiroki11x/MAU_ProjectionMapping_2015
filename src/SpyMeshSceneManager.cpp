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
    elements.push_back(new StartVideo());
    elements.push_back(new ArtSpyDeforming());
    elements.push_back(new TwitterRain());
    elements.push_back(new SpyMeshIntro());
    elements.push_back(new SpyMesh());
    elements.push_back(new IconStream());
    elements.push_back(new GlidShoot());
    elements.push_back(new WaveFractal());
    elements.push_back(new GlassBreak());
    elements.push_back(new LineFractal());
    elements.push_back(new EndingVideo());
    //elements.push_back(new StringNetwork());
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
            elements[elementIndex]->stop();
            elementIndex = 0;
            return;
        case '2':
            elements[elementIndex]->stop();
            elementIndex = 1;
            return;
        case '3':
            elements[elementIndex]->stop();
            elementIndex = 2;
            return;
        case '4':
            elements[elementIndex]->stop();
            elementIndex = 3;
            return;
        case '5':
            elements[elementIndex]->stop();
            elementIndex = 4;
            return;
        case '6':
            elements[elementIndex]->stop();
            elementIndex = 5;
            return;
        case '7':
            elements[elementIndex]->stop();
            elementIndex = 6;
            return;
        case '8':
            elements[elementIndex]->stop();
            elementIndex = 7;
            return;
        case '9':
            elements[elementIndex]->stop();
            elementIndex = 8;
            return;
        case '0':
            elements[elementIndex]->stop();
            elementIndex = 9;
            return;
        case '-':
            elements[elementIndex]->stop();
            elementIndex = 10;
            return;
       /* case '^':
            elements[elementIndex]->stop();
            elementIndex = 11;
            return;*/
        case '#':
            elements[elementIndex]->stop();
            splitView = !splitView;
            return;
    }
    elements.at(elementIndex)->keyPressed(key);
};
