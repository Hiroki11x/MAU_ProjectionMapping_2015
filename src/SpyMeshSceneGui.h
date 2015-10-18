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
#define MAX_WAVE 5

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
    
    bool drawDNAmode = false;
    float dnaWindowHeight;
    
    bool drawTargetLineMode = false;
    bool targetMoving;
    float targetWaitFrame;
    float targetCircleSize;
    ofVec2f position;
    ofVec2f nextPosition;
    ofVec2f difPosition;
    
    int befAgentNum;
    vector<newAgentWave> newAgentWaves;
    
    
    bool drawWaveMode = false;
    bool creatingNewWave = false;
    int waveWindowHeight = 20;
    int waveNum = 0;
    void updateWave();
    void addWave();
    void eraseWave();
    typedef struct{
        ofVboMesh waveMesh;
        int nextInterval;
        int intervalCounter;
    } Wave;
    vector<Wave> waves;

    
private:
    void drawBackLine();
    void drawEntry(vector<AgentAnalysis> agents);
    void drawAnalyzer();
    void drawFoundation();
    void drawWave();
    void drawDNA();
    void drawTargetLine();
    void initFoundation();
    int entryNum();
};
#endif
