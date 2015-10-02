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

#define MAX_VERTICES 10000

class ModelDrawer {
public:
    int verticesSize;
    ofVboMesh mesh;
    ofVec3f vertices[MAX_VERTICES];
    
    inline void drawModel(float scale){
        ofEnableDepthTest();
        mesh.drawWireframe();
    };
    
    inline void setVerices(vector<ofVec3f> newVec,float size){
        int preSize = verticesSize;
        verticesSize += newVec.size();
        for(int i = 0; i < newVec.size(); i++){
            if(i + preSize > MAX_VERTICES - 1){return;}
            vertices[i + preSize] = newVec.at(i) * size;
        }
    };
    
    inline ofVec3f addVertices(int i){
        if(i < verticesSize){
            mesh.addVertex(vertices[i]);
            return vertices[i];
        }
    };
    
    ModelDrawer(){
        verticesSize = 0;
        mesh.clear();
    };
};
#endif
