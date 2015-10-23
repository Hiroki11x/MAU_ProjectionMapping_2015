//
//  LineFractal.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/21.
//
//
#include "LineFractal.h"

void LineFractal::init(){
    
    reset();
    
}

void LineFractal::reset(){
    firstLine = new LineFractalComp();
    firstLine->generation = 0;
    firstLine->lineNum = ofRandom(5,10);
    firstLine->maxDeg = ofRandom(60,180);
    firstLine->lineLength = ofRandom(50,100);
    firstLine->firstStartLinePoint = ofRandom(50,100);
    firstLine->firstEndLinePoint = firstLine->firstStartLinePoint + firstLine->lineLength;
    firstLine->c = ofColor::fromHsb(ofRandom(0,255), 255, 255);
    
}
void LineFractal::update(){
    

    firstLine->updateLineFrac();
    
}
void LineFractal::draw(){
    ofPushMatrix();
    ofSetLineWidth(3);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    firstLine->drawLineFrac();
    ofPopMatrix();
}
void LineFractal::onMouseDown(int x, int y){}

void LineFractal::keyPressed(int key){
    switch (key) {
        case 'R':
            reset();
            break;
            
        default:
            break;
    }
}

void LineFractal::stop(){}

void LineFractal::LineFractalComp::updateLineFrac(){

    if(expanding){
        deg++;
        if(deg > maxDeg){
            expanding = false;
            if(!generatedChild){
                children.push_back(new LineFractalComp(*this));
                children.push_back(new LineFractalComp(*this));
                children.push_back(new LineFractalComp(*this));
                generatedChild = true;
            }
        }
    }else {
        deg--;
        if(deg <= 0){
            expanding = true;
        }
    }
    for(int i = 0; i < children.size(); i++){
        children.at(i)->updateLineFrac();
    }
}

void LineFractal::LineFractalComp::drawLineFrac(){
    
    for(int i = 0; i < lineNum; i++){
        ofSetColor(c);
        ofRotateZ(deg / (float)lineNum);
        ofLine(0, firstStartLinePoint, 0,firstEndLinePoint);
    }
    for(int i = 0; i < children.size(); i++){
        ofPushMatrix();
        children.at(i)->drawLineFrac();
        ofPopMatrix();
    }
}

LineFractal::LineFractalComp::LineFractalComp(LineFractalComp const &parent){
    generation = parent.generation + 1;
    deg = 0;
    lineNum = ofRandom(3,10);
    c = ofColor::fromHsb(ofRandom(0,255), 255, 255);
    //rotateRadius = parent.rotateRadius;
    if(ofRandom(10) > 5){
        maxDeg = parent.maxDeg * 2.0;
        lineLength = parent.lineLength * 2.0;
    }else{
        maxDeg = parent.maxDeg / 2.0;
        lineLength = parent.lineLength / 2.0;
    }
    
    if(ofRandom(10) > 5){
        firstStartLinePoint = parent.firstEndLinePoint;
        firstEndLinePoint = firstStartLinePoint + lineLength;
    }else{
        firstEndLinePoint = parent.firstStartLinePoint;
        firstStartLinePoint = firstEndLinePoint - lineLength;
    }
    if(generation >= MAX_GENE){
        generatedChild = true;
    }
}