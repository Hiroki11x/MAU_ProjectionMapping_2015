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

class ModelDrawer {
public:
    int verticesSize;
    bool drawEdge[10000][10000];
    ofVboMesh mesh;
    ofVec3f vertices[10000];
    
    inline void drawModel(float scale){
//        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
//        mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
//        mesh.setMode(OF_PRIMITIVE_POINTS);
        mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
        
        ofEnableDepthTest();
        ofSetColor(50,255,50,70);
//        mesh.drawWireframe();
        mesh.draw();
    };
    
    inline void setVerices(vector<ofVec3f> newVec,float size){
        int preSize = verticesSize;
        verticesSize += newVec.size();
        cout << verticesSize << endl;
        for(int i = 0; i < newVec.size(); i++){
            if(i + preSize > 9999){return;}
            //vertices[i + preSize] = newVec.at(i);
            vertices[i + preSize] = newVec.at(i) * size; //garally用
            if(i < newVec.size() - 10){
                mesh.addTriangle(i,i+5,i+10);
            }
        }
    };
    
    inline ofVec3f addVertices(int i){
        if(i < verticesSize){
            mesh.addVertex(vertices[i]);
            return vertices[i];
        }
        mesh.indices.clear();
    };
    
    ModelDrawer(){
        verticesSize = 0;
        mesh.clear();
    };
};
#endif
