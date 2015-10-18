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
 
    ofxTrueTypeFontUL2 * font;
    ofxTrueTypeFontUL2 * nameFont;
    
    int befAgentNum;
    vector<newAgentWave> newAgentWaves;
    
private:
    void drawBackLine();
    void drawEntry(vector<AgentAnalysis> agents);
    int entryNum();
    
    class EntryEntity;
};
#endif
