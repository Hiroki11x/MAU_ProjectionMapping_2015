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
#define CIRCUIT_HEIGHT_NUM 10

class CircuitDrawer {
public:
    enum Direction{
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    
    void init();
    void drawCircuit();
    void updateCircuite();
    bool setNextPoint(Direction nextDirection, int n);
    void setRandomPoint(int n);
    void reset();
    ofVboMesh circuit[4];
    ofVec3f targetPoint[4];
    ofVec3f lineStartPoint[4];
    ofVec3f points[CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM];
    bool usedPoint[CIRCUIT_WIDTH_NUM * CIRCUIT_HEIGHT_NUM];
    bool arrivedNextPoint[4];
    float positionCounter[4]; //0~1
    int nextIndex[4];
    int addedPoint;
    int waitFrames;
};
#endif
