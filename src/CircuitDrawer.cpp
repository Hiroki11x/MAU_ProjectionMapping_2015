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
        points[i] = ofVec3f((i  % CIRCUIT_WIDTH_NUM) * CIRCUIT_POINT_INTERVAL - 10,
                            (i / CIRCUIT_HEIGHT_NUM) * CIRCUIT_POINT_INTERVAL - 116,0);
    }
    
    reset();
}

void CircuitDrawer::reset(){
    for(int i = 0; i < CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM; i++){
        usedPoint[i] = false;
    }
    for(int n = 0; n < 10; n++){
        circuit[n].useColors = false;
        circuit[n].clear();
        setRandomPoint(n);
        circuit[n].addVertex(targetPoint[n]);
        arrivedNextPoint[n] = true;
        positionCounter[n] = 0;
        addedPoint = 10;
        
        lineColors[n].setHsb(ofRandom(120, 240), 255, 255);
    }

    
    waitFrames = 0;
}

void CircuitDrawer::updateCircuite(){
    
    for(int n = 0; n < 10; n++){
        if(arrivedNextPoint[n] && addedPoint < CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM){
            //最初と最後以外はニコ入れる
            if(addedPoint != 1 && addedPoint != CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM) circuit[n].addVertex(targetPoint[n]);
            circuit[n].addVertex(targetPoint[n]);
            lineStartPoint[n] = targetPoint[n];
            arrivedNextPoint[n] = false;
            positionCounter[n] = 0;
            Direction nextDirection = Direction(ofRandom(8));
            for(int i = 0; true; i++){
                if(setNextPoint(nextDirection, n)){break;}
                if(i == 3 && mode == NORMAL){
                    circuit[n].addVertex(targetPoint[n]);
                    setRandomPoint(n);
                    circuit[n].addVertex(targetPoint[n]);
                    break;
                }
                if(i >= 7 && mode != NORMAL){
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
            if(!boxMode){
                positionCounter[n] += ofRandom(0.3, 1.0);
            }else{
                positionCounter[n] += ofRandom(0.1, 0.2);
            }
            if(positionCounter[n] > 1.0){
                arrivedNextPoint[n] = true;
            }
        }
    }
    if(addedPoint == CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM) {
        waitFrames++;
        if(waitFrames > 30) reset();
    }
}

void CircuitDrawer::drawCircuit(){
    if(boxMode){
        drawBoxCircuit();
        return;
    }
    ofPushMatrix();
    ofPushStyle();
    ofSetLineWidth(3);
    glPointSize(15);
    for(int n = 0; n < 10; n++){
        if(randomColor){
            ofSetColor(lineColors[n] ,255);
        }else{
            ofSetColor(100, 255, 255, 255);
            //ofSetColor(100, 255, 255, 100);
        }
        circuit[n].setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
        circuit[n].draw();
        circuit[n].setMode(ofPrimitiveMode::OF_PRIMITIVE_POINTS);
        circuit[n].draw();
    }
    if(addedPoint != CIRCUIT_HEIGHT_NUM * CIRCUIT_WIDTH_NUM){
        ofSetColor(0, 255, 255);
        ofSetLineWidth(1);
        for(int n = 0; n <4; n++){
            if(randomColor){
                ofSetColor(lineColors[n] ,255);
            }else{
                //ofSetColor(100, 255, 255, 255);
                ofSetColor(100, 255, 255, 255);
            }
            ofLine(lineStartPoint[n], lineStartPoint[n] + positionCounter[n] *(targetPoint[n] - lineStartPoint[n]));
        }
    }
    ofPopStyle();
    ofPopMatrix();
}

void CircuitDrawer::drawBoxCircuit(){
    ofPushMatrix();
    ofPushStyle();
    ofSetBackgroundAuto(false);
    ofSetLineWidth(3);
    ofEnableAlphaBlending();
    glPointSize(45);
    ofSetColor(0,0,0,20);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    for(int n = 0; n < 10; n++){
        if(randomColor){
            //ofSetColor(lineColors[n] ,100);
            ofSetColor(lineColors[n] ,255);
        }else{
            //ofSetColor(100, 255, 255, 100);
            ofSetColor(100, 255, 255, 255);
        }
        /*circuit[n].setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
        circuit[n].draw();
        ofRect(circuit[n].vertices.at(circuit[n].vertices.size() - 1),45,45);*/
        ofCircle(lineStartPoint[n] + positionCounter[n] *(targetPoint[n] - lineStartPoint[n]), 15);
    }
    if(addedPoint != CIRCUIT_HEIGHT_NUM * CIRCUIT_WIDTH_NUM){
        //ofSetColor(0, 255, 255);
        ofSetLineWidth(1);
        for(int n = 0; n <10; n++){
            if(randomColor){
                //ofSetColor(lineColors[n] ,100);
                ofSetColor(lineColors[n] ,255);
            }else{
                //ofSetColor(100, 255, 255, 100);
                ofSetColor(100, 255, 255, 100);
                
            }
            ofLine(lineStartPoint[n], lineStartPoint[n] + positionCounter[n] *(targetPoint[n] - lineStartPoint[n]));
        }
    }
    ofPopStyle();
    ofPopMatrix();
}

void CircuitDrawer::initBoxCircuit(){
    boxMode = true;
    ofSetBackgroundAuto(false);
}

void CircuitDrawer::endBoxCircuit(){
    boxMode = false;
    ofSetBackgroundAuto(true);
}

bool CircuitDrawer::setNextPoint(Direction nextDirection, int n){
    switch (nextDirection) {
        
        case UP:
            if(!(mode == NORMAL || mode == VERTICAL)) return false;
            if((nextIndex[n] - CIRCUIT_WIDTH_NUM > 0) && (!usedPoint[nextIndex[n] - CIRCUIT_WIDTH_NUM]))
            {
                nextIndex[n] = nextIndex[n] - CIRCUIT_WIDTH_NUM;
                targetPoint[n] = points[nextIndex[n]];
                usedPoint[nextIndex[n]] = true;
                return true;
            }
            break;
        case DOWN:
            if(!(mode == NORMAL || mode == VERTICAL)) return false;
            if((nextIndex[n] + CIRCUIT_WIDTH_NUM < CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM) && (!usedPoint[nextIndex[n] + CIRCUIT_WIDTH_NUM]))
            {
                nextIndex[n] = nextIndex[n] + CIRCUIT_WIDTH_NUM;
                targetPoint[n] = points[nextIndex[n]];
                usedPoint[nextIndex[n]] = true;
                return true;
            }
            break;
        case RIGHT:
            if(!(mode == NORMAL || mode == HORIZONTAL)) return false;
            if((nextIndex[n] + 1 < CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM) && (!usedPoint[nextIndex[n] + 1]) && ((nextIndex[n] + 1) % CIRCUIT_WIDTH_NUM != 0))
            {
                nextIndex[n] = nextIndex[n] + 1;
                targetPoint[n] = points[nextIndex[n]];
                usedPoint[nextIndex[n]] = true;
                return true;
            }
            break;
        case LEFT:
            if(!(mode == NORMAL || mode == HORIZONTAL)) return false;
            if(nextIndex[n] - 1 > 0 && !usedPoint[nextIndex[n] -1] && (nextIndex[n] - 1) % CIRCUIT_WIDTH_NUM != CIRCUIT_WIDTH_NUM - 1)
            {
                nextIndex[n] = nextIndex[n] - 1;
                targetPoint[n] = points[nextIndex[n]];
                usedPoint[nextIndex[n]] = true;
                return true;
            }
            break;
        case UP_RIGHT:
            if(!(mode == NORMAL || mode == RIGHT_UP || mode == CROSS)) return false;
            if(nextIndex[n] - CIRCUIT_WIDTH_NUM + 1 > 0
               && !usedPoint[nextIndex[n] - CIRCUIT_WIDTH_NUM + 1]
               && (nextIndex[n] - CIRCUIT_WIDTH_NUM + 1) % CIRCUIT_WIDTH_NUM != 0)
            {
                nextIndex[n] = nextIndex[n] - CIRCUIT_WIDTH_NUM + 1;
                targetPoint[n] = points[nextIndex[n]];
                usedPoint[nextIndex[n]] = true;
                return true;
            }
            break;
        case UP_LEFT:
            if(!(mode == NORMAL || mode == LEFT_UP || mode == CROSS)) return false;
            if(nextIndex[n] - CIRCUIT_WIDTH_NUM - 1  > 0
               && !usedPoint[nextIndex[n] - CIRCUIT_WIDTH_NUM - 1]
               && (nextIndex[n] - CIRCUIT_WIDTH_NUM - 1) % CIRCUIT_WIDTH_NUM != CIRCUIT_WIDTH_NUM - 1)
            {
                nextIndex[n] = nextIndex[n] - CIRCUIT_WIDTH_NUM - 1;
                targetPoint[n] = points[nextIndex[n]];
                usedPoint[nextIndex[n]] = true;
                return true;
            }
            break;
        case DOWN_RIGHT:
            if(!(mode == NORMAL || mode == LEFT_UP || mode == CROSS)) return false;
            if(nextIndex[n] + CIRCUIT_WIDTH_NUM + 1 < (CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM)
               && !usedPoint[nextIndex[n] + CIRCUIT_WIDTH_NUM + 1]
               && (nextIndex[n] + CIRCUIT_WIDTH_NUM + 1) % CIRCUIT_WIDTH_NUM != 0)
            {
                nextIndex[n] = nextIndex[n] + CIRCUIT_WIDTH_NUM + 1;
                targetPoint[n] = points[nextIndex[n]];
                usedPoint[nextIndex[n]] = true;
                return true;
            }
            break;
        case DOWN_LEFT:
            if(!(mode == NORMAL || mode == RIGHT_UP || mode == CROSS)) return false;
            if(nextIndex[n] + CIRCUIT_WIDTH_NUM - 1 < (CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM)
               && !usedPoint[nextIndex[n] + CIRCUIT_WIDTH_NUM - 1]
               && (nextIndex[n] + CIRCUIT_WIDTH_NUM - 1) % CIRCUIT_WIDTH_NUM != CIRCUIT_WIDTH_NUM - 1)
            {
                nextIndex[n] = nextIndex[n] + CIRCUIT_WIDTH_NUM - 1;
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
    lineStartPoint[n] = targetPoint[n];
    usedPoint[nextIndex[n]] = true;
    lineColors[n].setHsb(ofRandom(120, 240), 255, 255);
}

void CircuitDrawer::changeMode(Mode nextMode){
    mode = nextMode;
}