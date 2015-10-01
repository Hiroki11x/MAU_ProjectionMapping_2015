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
    ofVec3f vertices[10000];
    int verticesSize;
    bool drawEdge[10000][10000];
    ofVboMesh mesh;
    
    inline void drawModel(float scale){
        ofEnableDepthTest();
        ofSetColor(50,255,50);
        //ofNoFill();
        /*for(int i = 0; i < verticesSize; i++){
            for(int j = i + 1; j < verticesSize; j++){
                if(drawEdge[i][j]){
                    ofLine(vertices[i], vertices[j]);
                }
            }
        }*/
//        mesh.draw();
        mesh.drawWireframe();
    };
    
    
    
    inline void setVerices(vector<ofVec3f> newVec){
        int preSize = verticesSize;
        verticesSize += newVec.size();
        cout << verticesSize << endl;
        for(int i = 0; i < newVec.size(); i++){
            vertices[i + preSize] = newVec.at(i);
            //mesh.addVertex(newVec.at(i));
            if(i < newVec.size() - 10){
                //mesh.addTriangle(i,i+5,i+10);
            }
        }
    };
    
    inline ofVec3f addVertices(int i){
        if(i < verticesSize){
            mesh.addVertex(vertices[i]);
            return vertices[i];
        }
        //mesh.indices.clear();
    };
    
    ModelDrawer(){
        verticesSize = 0;
        mesh.clear();
        //mesh.setMode(OF_PRIMITIVE_POINTS);
    };
};
#endif /* _DModelDrawer_hpp */
