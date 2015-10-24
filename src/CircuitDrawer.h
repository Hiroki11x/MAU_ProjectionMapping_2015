//
//  CircuitDrawer.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/14.
//
//

#ifndef CircuitDrawer_h
#define CircuitDrawer_h

#include "ofMain.h"

//#define CIRCUIT_POINT_INTERVAL 45
#define CIRCUIT_POINT_INTERVAL 100
#define CIRCUIT_WIDTH_NUM 18
#define CIRCUIT_HEIGHT_NUM 18

class CircuitDrawer {
public:
    enum Direction{
        UP,
        DOWN,
        LEFT,
        RIGHT,
        UP_RIGHT,
        UP_LEFT,
        DOWN_RIGHT,
        DOWN_LEFT
    };
    
    enum Mode{
        NORMAL,
        HORIZONTAL,
        VERTICAL,
        RIGHT_UP,
        LEFT_UP,
        CROSS
    };
    
    void init();
    void drawCircuit();
    void updateCircuite();
    void setRandomPoint(int n);
    void changeMode(Mode nextMode);
    void reset();
    void drawBoxCircuit();
    void initBoxCircuit();
    void endBoxCircuit();
    bool setNextPoint(Direction nextDirection, int n);
    
    ofVboMesh circuit[10];
    ofVec3f targetPoint[10];
    ofVec3f lineStartPoint[10];
    ofVec3f points[CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM];
    ofColor lineColors[10];
    Mode mode = NORMAL;
    
    int nextIndex[10];
    int addedPoint;
    int waitFrames;
    bool usedPoint[CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM];
    bool arrivedNextPoint[10];
    bool randomColor = true;
    float positionCounter[10]; //0~1
    bool boxMode = false;
};
#endif
