//
//  TrailRenderer.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/02.
//
//
#include "TrailRenderer.h"

void TrailRenderer::changeMode(bool rotate, bool convergence, bool acceralate){
    this->rotateMode = rotate;
    this->convergenceMode = convergence;
    this->acceralateMode = acceralate;
}

void TrailRenderer::drawTrailer(){
    
    ofPushMatrix();
    ofPushStyle();
    
    ofVec3f trailPosition = startPoint + float(position/endPosition) * ( targetPoint - startPoint );
    
    ofSetColor(50,255,50);
    ofTranslate(0,trailPosition.y,trailPosition.z );
    for(int i = 0; i < trailNum; i++){
        ofPushMatrix();
        ofRotateX(degree + 360 * i / trailNum);
        
        switch (this->trailShape) {
            case SimpelSphere:
                ofDrawSphere(trailPosition.x,0,radius, size);
                break;
            case SimpleBox:
                ofDrawBox(trailPosition.x,0,radius, size);
                break;
            case SimpleLine:
                ofLine(trailPosition.x, 0, radius, trailPosition.x - 100, 0 ,radius);
                break;
            case MultiBox:
                for(int i = 0; i < 9; i++){
                    ofRotateX( -i * 5);
                    ofDrawBox(trailPosition.x - 200 * i,0,radius, size  * (1.0 - float(i)/9.0));
                }
                break;
            case MultiSphere:
                for(int i = 0; i < 9; i++){
                    ofRotateX( -i * 5);
                    ofDrawSphere(trailPosition.x - 200 * i,0,radius, size  * (1.0 - float(i)/9.0));
                }
                break;
            default:
                break;
        }
        ofPopMatrix();
    }
    ofPopMatrix();
    ofPopStyle();
}

void TrailRenderer::update(){

    position += 0.7;
    size /= 1.005;
    if(rotateMode){
        degree+=2;
    }
    if(acceralateMode){
        position *= 1.1;
    }
    if(convergenceMode){
        radius /= 1.2;
    }
}

TrailRenderer::TrailRenderer(ofVec3f sPoint, ofVec3f tPoint ,TrailShape shape, int trailNum, float radius){
    this->startPoint = sPoint;
    this->targetPoint = tPoint;
    this->trailShape = shape;
    this->trailNum = trailNum;
    this->position = 0;
    this->radius = radius;
    this->endPosition = 300;
    this->size = 100;
    this->rotateMode = true;
    this->trailShape = MultiSphere;
}