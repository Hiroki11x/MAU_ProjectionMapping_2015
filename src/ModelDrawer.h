//
//  3DModelDrawer.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/01.
//
//
#ifndef _ModelDrawer_h
#define _ModelDrawer_h

#include "ofMain.h"

#define MAX_VERTICES 150000
#define MAX_INDICES 150000
#define COLORED_MESH_PER_HANDRED_TRIANGLE 20
#define EXPAND_MESH_NUM 10

class ModelDrawer {
public:
    enum ColoredMeshMode{
        LINE,
        RANDOM,
        AFFECTED_GLAVITY_GLASS,
    };
    
    int addedIndicesSize;
    int coloredIndices[MAX_INDICES / 3 / COLORED_MESH_PER_HANDRED_TRIANGLE];
    int coloredIndex;
    int coloredMeshSize;
    int indicesSize;
    int verticesSize;
    int grassFrames;
    bool isExpandingColoredMesh;
    
    vector<ofIndexType> indices;
    ColoredMeshMode coloredMeshMode;
    ofPrimitiveMode primitiveMode;
    ofVboMesh mesh;
    ofVboMesh coloredPartMesh;
    ofVboMesh randomExpandMesh;
    ofVec3f vertices[MAX_VERTICES];
    ofVec3f coloredMeshesVec[MAX_INDICES / COLORED_MESH_PER_HANDRED_TRIANGLE];
    ofVec3f randomExpandMeshesVec[EXPAND_MESH_NUM * 3];
    ofColor parsentFrameColor = ofColor(51,153,204,255);
    //ofColor parsentFrameColor = ofColor(51,153,204,100); //ofSetColor(80,120,80,100);
    ofColor parsentColor = ofColor(204,255,255,255);
    //ofColor parsentColor = ofColor(204,255,255,200); //ofSetColor(50,255,50,200);
    
    ofVec3f addVertex();
    void changeColoredPartMesh();
    void changeColoredMode(ColoredMeshMode mode);
    void changeRandomExpandMesh();
    void drawColoredMesh();
    void drawModel(float scale, bool fill = false);
    void drawRandomExpandMesh(float scale);
    void drawPercentage();
    void setPrimitiveMode(ofPrimitiveMode primitiveMode);
    void setVertices(vector<ofVec3f> newVec, vector<ofIndexType> newIndices,float size);
    void updateColoredMesh(float size);
    void reset();
    
    ModelDrawer();
};
#endif
