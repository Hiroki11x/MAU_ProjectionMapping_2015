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

#define CIRCUIT_POINT_INTERVAL 90
#define CIRCUIT_WIDTH_NUM 12
#define CIRCUIT_HEIGHT_NUM 12

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
    bool setNextPoint(Direction nextDirection, int n);
    
    ofVboMesh circuit[4];
    ofVec3f targetPoint[4];
    ofVec3f lineStartPoint[4];
    ofVec3f points[CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM];
    Mode mode = NORMAL;
    
    int nextIndex[4];
    int addedPoint;
    int waitFrames;
    bool usedPoint[CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM];
    bool arrivedNextPoint[4];
    float positionCounter[4]; //0~1
};
#endif
