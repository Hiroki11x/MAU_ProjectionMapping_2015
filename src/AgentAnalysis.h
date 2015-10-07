//
//  AgentAnalysis.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/07.
//
//
#ifndef AgentAnalysis_h
#define AgentAnalysis_h

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class AgentAnalysis {
public:
    
    static vector<ofVec3f> vertices;
    static void init(float scale);
    
    ofMesh mesh;
    ofVec3f targetPodsition;
    ofVec3f position;
    ofTrueTypeFont fontDrawer;

    void drawAgent();
    void drawLine();
    bool removeVertices();
    float rotateSpeed;
    
    AgentAnalysis(ofVec3f pos);
};
#endif
