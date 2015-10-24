//
//  WaveFractal.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/19.
//
//
#ifndef WaveFractal_h
#define WaveFractal_h

#include "ofMain.h"
#include "SceneElement.h"

#define MAX_WAVE_FRACTAL 30
#define MAX_GENERATION 7
#define MAX_CHILDREN 3

class WaveFractal : public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    virtual void stop() override;
    
    void reset();
    
    class Wave{
    public:
        ofVec3f centerPosition;
        float rotateSpeed;
        float frequency;
        float radius;
        float deg;
        bool generatedNextWave;
        int frameCounter;
        int nextWaveFrames;
        int generation;
        vector<Wave> children;
        
        void drawWavePoint();
        void updateWave();
        Wave(int gen);
        Wave(){};
    };
    Wave firstWave;
    ofEasyCam cam;
};
#endif
