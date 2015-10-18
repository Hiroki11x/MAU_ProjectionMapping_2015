//
//  SpyMeshSceneGui.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/16.
//
//
#ifndef SpyMeshSceneGui_h
#define SpyMeshSceneGui_h

#include "ofMain.h"
#include "ofxTrueTypeFontUL2.h"
#include "AgentAnalysis.h"
#include "ofxAssimpModelLoader.h"

#define MIDDLE_RATE 1.15
#define OUTSIDE_RATE 1.65

class SpyMeshSceneGui {
public:
    typedef struct{
        float size;
        float index;
        int shapeType;
        float rotation;
    } newAgentWave;
    
    void init();
    void drawGui(vector<AgentAnalysis> agents);
    void updateGui();
    
 
    ofxAssimpModelLoader DNAmodel;
    ofxTrueTypeFontUL2 * font;
    ofxTrueTypeFontUL2 * nameFont;
    ofVboMesh insideCircleMesh;
    ofVboMesh middleCircleMesh;
    ofVboMesh outsideCircleMesh;
    
    float insideSpeed = -5.0;
    float middleSpeed = 8.0;
    float outsideSpeed = 1.0;
    float insideDeg;
    float middleDeg;
    float outsideDeg;
    
    int befAgentNum;
    vector<newAgentWave> newAgentWaves;
    
private:
    void drawBackLine();
    void drawEntry(vector<AgentAnalysis> agents);
    void drawAnalyzer();
    void drawFoundation();
    void initFoundation();
    int entryNum();
};
#endif
