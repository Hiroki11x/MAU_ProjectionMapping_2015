//
//  LineFractal.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/21.
//
//
#ifndef LineFractal_h
#define LineFractal_h

#include "ofMain.h"
#include "SceneElement.h"
#define MAX_GENE 4

class LineFractal : public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    virtual void stop() override;
    void reset();
    
    class LineFractalComp{
    public:
        int generation;
        int lineNum;
        bool expanding;
        bool generatedChild;
        float maxDeg;
        float deg;
        float rotateRadius;
        float lineLength;
        float firstStartLinePoint;
        float firstEndLinePoint;
        vector<LineFractalComp *> children;
        
        void drawLineFrac();
        void updateLineFrac();
        ofColor c;
        LineFractalComp(){};
        LineFractalComp(LineFractalComp const &parent);
    };
    
    LineFractalComp * firstLine;
};
#endif
