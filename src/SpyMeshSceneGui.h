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
    ofColor agentNameColor = ofColor(220, 220, 255, 255); //210, 255, 210,220
    ofColor agentBarColor = ofColor(255,0,102,200); //80, 230, 80, 150
    ofColor agentEntryFrameColor = ofColor(204,255,255,50); //80,120,80,100);
    ofColor agentEntryBackColor = ofColor(10,10,18,200); //ofNoFill200, 255, 200,80
    ofColor agentEntryNewWaveColor = ofColor(100, 100, 200,100);//100, 255, 100,100
    ofColor agentAnalistLineColor = ofColor(255,0,102, 100); //255, 255, 255, 100);
    ofColor agentAnalistColor = ofColor(220, 220, 255, 255); //(100, 255, 100, 150);
    
    //----------------------------------------------------------
    //DNA
    //----------------------------------------------------------
    bool drawDNAmode = false;
    float dnaWindowHeight;
    ofxAssimpModelLoader DNAmodel;
    ofColor dnaFrameColor = ofColor(204,255,255,50); //80,120,80,100);
    ofColor dnaBackColor = ofColor(10,10,18,200);  //(50,255,50,200);ofNoFill();
    ofColor dnaModelColor = ofColor(200,255,200,200);

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
    ofColor targetColor = ofColor(255,255,255,150);
    
    //----------------------------------------------------------
    //Wave
    //----------------------------------------------------------
    typedef struct{
        ofVboMesh waveMesh;
        int nextInterval;
        int intervalCounter;
    } Wave;
    int waveWindowHeight = 20;
    int waveNum = 1;
    bool drawWaveMode = false;
    bool creatingNewWave = false;
    void updateWave();
    void addWave();
    void eraseWave();
    vector<Wave> waves;
    ofColor waveFrameColor = ofColor(204,255,255,50); //(80,120,80,100);
    ofColor waveBackColor = ofColor(10,10,18,200); //(100,180,100,100);
    ofColor waveColor = ofColor(51,255,102);

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
    //ofColor foundInsideColor = ofColor(70, 170, 255,50); //(70, 255, 70,50);
    ofColor foundInsideColor = ofColor(70, 170, 255,255);
    //ofColor foundMiddleColor = ofColor(200, 245, 240,50); //60, 245, 60,50);
    ofColor foundMiddleColor = ofColor(200, 245, 240,255);
    //ofColor foundOutsideColor = ofColor(100, 200, 200,50); //ofSetColor(100, 255, 100,50);
    ofColor foundOutsideColor = ofColor(100, 200, 200,255);

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