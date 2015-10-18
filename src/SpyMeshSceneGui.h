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
    void init();
    void drawGui(vector<AgentAnalysis> agents);
    void updateGui();
 
    //----------------------------------------------------------
    //AgentEntry
    //----------------------------------------------------------
    typedef struct{
        float size;
        float index;
        int shapeType;
        float rotation;
    } newAgentWave;
    
    int befAgentNum;
    vector<newAgentWave> newAgentWaves;
    ofxTrueTypeFontUL2 * font;
    ofxTrueTypeFontUL2 * nameFont;
    
    //----------------------------------------------------------
    //DNA
    //----------------------------------------------------------
    bool drawDNAmode = false;
    float dnaWindowHeight;
    ofxAssimpModelLoader DNAmodel;

    //----------------------------------------------------------
    //TargetLine
    //----------------------------------------------------------
    bool drawTargetLineMode = false;
    bool targetMoving;
    float targetWaitFrame;
    float targetCircleSize;
    ofVec2f position;
    ofVec2f nextPosition;
    ofVec2f difPosition;
    
    //----------------------------------------------------------
    //Wave
    //----------------------------------------------------------
    typedef struct{
        ofVboMesh waveMesh;
        int nextInterval;
        int intervalCounter;
    } Wave;
    int waveWindowHeight = 20;
    int waveNum = 0;
    bool drawWaveMode = false;
    bool creatingNewWave = false;
    void updateWave();
    void addWave();
    void eraseWave();
    vector<Wave> waves;
    

    //----------------------------------------------------------
    //Found
    //----------------------------------------------------------
    float insideSpeed = -5.0;
    float middleSpeed = 8.0;
    float outsideSpeed = 1.0;
    float insideDeg;
    float middleDeg;
    float outsideDeg;
    ofVboMesh insideCircleMesh;
    ofVboMesh middleCircleMesh;
    ofVboMesh outsideCircleMesh;

private:
    void drawBackLine();
    void drawEntry(vector<AgentAnalysis> agents);
    void drawAnalyzer();
    void drawFoundation();
    void drawWave();
    void drawDNA();
    void drawTargetLine();
    void initFoundation();
};
#endif