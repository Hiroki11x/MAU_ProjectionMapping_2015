//
//  GraphGuiDrawer.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/15.
//
//
#ifndef GraphGuiDrawer_h
#define GraphGuiDrawer_h

#include "ofMain.h"
#include "ofxTrueTypeFontUL2.h"

class GraphGuiDrawer{
public:
    enum GraphMode{
        RECT_BAR,
        WAVE,
        CIRCLE
    };
    
    void drawGraphGui();
    void drawRectBarGraph();
    void drawWaveGraph();
    void drawCircleGraph();
    void updateGraphParams();
    
    int graphNum;
    float graphParamatar[5];
    
    ofShader graphBack;
    ofVec2f scale;
    GraphMode mode;
    ofxTrueTypeFontUL2* font;
    
    GraphGuiDrawer();
};
#endif
