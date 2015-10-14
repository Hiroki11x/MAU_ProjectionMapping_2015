//
//  CircuitDrawer.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/14.
//
//

#include "CircuitDrawer.h"

void CircuitDrawer::init(){
    for(int i = 0; i < CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM; i++){
        points[i] = ofVec3f((i  % CIRCUIT_WIDTH_NUM) * CIRCUIT_POINT_INTERVAL - 38,
                            (i / CIRCUIT_HEIGHT_NUM) * CIRCUIT_POINT_INTERVAL - 116,0);
    }
    reset();
}

void CircuitDrawer::reset(){
    for(int i = 0; i < CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM; i++){
        usedPoint[i] = false;
    }
    for(int n = 0; n < 4; n++){
        circuit[n].useColors = false;
        circuit[n].clear();
        setRandomPoint(n);
        circuit[n].addVertex(targetPoint[n]);
        arrivedNextPoint[n] = true;
        positionCounter[n] = 0;
        addedPoint = 4;
    }
    waitFrames = 0;
}

void CircuitDrawer::updateCircuite(){
    
    
    for(int n = 0; n < 4; n++){
        if(arrivedNextPoint[n] && addedPoint < CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM){
            //最初と最後以外はニコ入れる
            if(addedPoint != 1 && addedPoint != CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM) circuit[n].addVertex(targetPoint[n]);
            circuit[n].addVertex(targetPoint[n]);
            lineStartPoint[n] = targetPoint[n];
            arrivedNextPoint[n] = false;
            positionCounter[n] = 0;
            Direction nextDirection = Direction(ofRandom(4));
            for(int i = 0; true; i++){
                if(setNextPoint(nextDirection, n)){break;}
                if(i == 1){
                    circuit[n].addVertex(targetPoint[n]);
                    setRandomPoint(n);
                    circuit[n].addVertex(targetPoint[n]);
                    break;
                }
                if(nextDirection != RIGHT) {
                    nextDirection = Direction(int(nextDirection) + 1);
                    continue;
                }
                nextDirection = UP;
            }
            addedPoint++;
        }else{
            positionCounter[n] += ofRandom(0, 0.5);
            if(positionCounter[n] > 1.0){
                arrivedNextPoint[n] = true;
            }
        }

    }
    if(addedPoint == CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM) {
        waitFrames++;
        if(waitFrames > 100) reset();
    }
}

void CircuitDrawer::drawCircuit(){
    ofPushMatrix();
    ofPushStyle();
    ofSetLineWidth(3);
    glPointSize(15);
    for(int n = 0; n < 4; n++){
        ofSetColor(0, 255, 255, 150);
        circuit[n].setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
        circuit[n].draw();
        ofSetColor(0, 255, 255, 150);
        circuit[n].setMode(ofPrimitiveMode::OF_PRIMITIVE_POINTS);
        circuit[n].draw();
    }
    ofSetColor(0,0,0,100 + 50 * sin(ofGetElapsedTimeMillis()/100.0));
    //ofRect(0, 0, ofGetWidth(), ofGetHeight());
    if(addedPoint != CIRCUIT_HEIGHT_NUM * CIRCUIT_WIDTH_NUM){
        ofSetColor(0, 255, 255);
        ofSetLineWidth(1);
        for(int n = 0; n <4; n++){
            ofLine(lineStartPoint[n], lineStartPoint[n] + positionCounter[n] *(targetPoint[n] - lineStartPoint[n]));
        }
    }
    ofPopStyle();
    ofPopMatrix();
}

bool CircuitDrawer::setNextPoint(Direction nextDirection, int n){
    switch (nextDirection) {
        
        case UP:
            if((nextIndex[n] - CIRCUIT_WIDTH_NUM > 0) && (!usedPoint[nextIndex[n] - CIRCUIT_WIDTH_NUM]))
            {
                nextIndex[n] = nextIndex[n] - CIRCUIT_WIDTH_NUM;
                targetPoint[n] = points[nextIndex[n]];
                usedPoint[nextIndex[n]] = true;
                return true;
            }
            break;
        case DOWN:
            if((nextIndex[n] + CIRCUIT_WIDTH_NUM < CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM) && (!usedPoint[nextIndex[n] + CIRCUIT_WIDTH_NUM]))
            {
                nextIndex[n] = nextIndex[n] + CIRCUIT_WIDTH_NUM;
                targetPoint[n] = points[nextIndex[n]];
                usedPoint[nextIndex[n]] = true;
                return true;
            }
            break;
        case RIGHT:
            if((nextIndex[n] + 1 < CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM) && (!usedPoint[nextIndex[n] + 1]) && ((nextIndex[n] + 1) % CIRCUIT_WIDTH_NUM != 0))
            {
                nextIndex[n] = nextIndex[n] + 1;
                targetPoint[n] = points[nextIndex[n]];
                usedPoint[nextIndex[n]] = true;
                return true;
            }
            break;
        case LEFT:
            if(nextIndex - 1 > 0 && !usedPoint[nextIndex[n] -1] && (nextIndex[n] - 1) % CIRCUIT_WIDTH_NUM != CIRCUIT_WIDTH_NUM - 1)
            {
                nextIndex[n] = nextIndex[n] - 1;
                targetPoint[n] = points[nextIndex[n]];
                usedPoint[nextIndex[n]] = true;
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

void CircuitDrawer::setRandomPoint(int n){
    int randomIndex = (int)ofRandom(CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM);
    while(usedPoint[randomIndex]){
        randomIndex++;
        if(randomIndex == CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM) randomIndex = 0;
    }
    nextIndex[n] = randomIndex;
    targetPoint[n] = points[nextIndex[n]];
    usedPoint[nextIndex[n]] = true;
}
