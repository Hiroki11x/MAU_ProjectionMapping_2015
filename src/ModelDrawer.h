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

class ModelDrawer {
public:
    int verticesSize;
    int indicesSize;
    ofVboMesh mesh;
    ofVec3f vertices[MAX_VERTICES];
    vector<ofIndexType> indices;
    
    inline void drawModel(float scale, bool fill = true){
        
        ofEnableDepthTest();
        ofPushStyle();
        ofSetLineWidth(1.0);
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        if(fill){
            mesh.draw(ofPolyRenderMode::OF_MESH_FILL);
        }else{
            mesh.drawWireframe();
        }
        ofPopStyle();
    };
    
    inline void setVerices(vector<ofVec3f> newVec, vector<ofIndexType> newIndices,float size){
        int preSize = verticesSize;
        verticesSize += newVec.size();
        for(int i = 0; i < newVec.size(); i++){
            if(i + preSize > MAX_VERTICES - 1){break;}
            vertices[i + preSize] = newVec.at(i) * size;
        }
        //cout << "indiceZize" << verticesSize << endl;

        
        int preIndiceSize = indicesSize;
        indicesSize += newIndices.size();
        cout << "indiceZize" << indicesSize << endl;
        for(int i = 0; i < newIndices.size(); i++){
            if(i + preIndiceSize > MAX_INDICES - 1){break;}
            indices[i + preIndiceSize] = newIndices.at(i);
        //    cout << "indice" << indices[i + preIndiceSize] << endl;
        }
    };
    
    inline ofVec3f addVertices(int i){
        
        if(i < MAX_INDICES/3 - 1 && i < indicesSize/3 - 1){
            //add 1triangle
            mesh.addVertex(vertices[int(indices[i * 3])]);
            mesh.addVertex(vertices[int(indices[i * 3 + 1])]);
            mesh.addVertex(vertices[int(indices[i * 3 + 2])]);
            
            /*mesh.addVertex(vertices[int(indices[i * 2])]);
            mesh.addVertex(vertices[int(indices[i * 2 + 1])]);*/
            mesh.addIndex(i * 3);
            mesh.addIndex(i * 3 + 1);
            mesh.addIndex(i * 3 + 2);
            
            return vertices[int(indices[i * 3])];
        }
        
    };
    
    ModelDrawer(){
        verticesSize = 0;
        indicesSize = 0;
        mesh.clear();
        mesh.enableIndices();
        indices = *new vector<ofIndexType>(MAX_INDICES);
    };
};
#endif
