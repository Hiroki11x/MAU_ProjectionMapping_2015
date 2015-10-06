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
    ofVec3f vertices[MAX_VERTICES];
    ofVec3f coloredMeshesVec[MAX_INDICES / COLORED_MESH_PER_HANDRED_TRIANGLE];
    
    ofVec3f addVertex(int i);
    void changeColoredPartMesh();
    void changeColoredMode(ColoredMeshMode mode);
    void drawColoredMesh();
    void drawModel(float scale, bool fill = false);
    void drawPercentage();
    void setPrimitiveMode(ofPrimitiveMode primitiveMode);
    void setVertices(vector<ofVec3f> newVec, vector<ofIndexType> newIndices,float size);
    void updateColoredMesh(float size);
    
    ModelDrawer();
};
#endif
