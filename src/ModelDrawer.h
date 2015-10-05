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
    int addedIndicesSize;
    ofVboMesh mesh;
    ofVec3f vertices[MAX_VERTICES];
    ofPrimitiveMode primitiveMode;
    vector<ofIndexType> indices;
    
    void drawPercentage();
    void setPrimitiveMode(ofPrimitiveMode primitiveMode);
    
    inline void drawModel(float scale, bool fill = false){
        
        ofEnableDepthTest();
        ofPushStyle();
        ofSetLineWidth(1.0);
        mesh.setMode(primitiveMode);
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
            switch(primitiveMode){
                case OF_PRIMITIVE_TRIANGLES:
                    mesh.addVertex(vertices[int(indices[i * 3])]);
                    mesh.addVertex(vertices[int(indices[i * 3 + 1])]);
                    mesh.addVertex(vertices[int(indices[i * 3 + 2])]);
                    
                    mesh.addIndex(i * 3);
                    mesh.addIndex(i * 3 + 1);
                    mesh.addIndex(i * 3 + 2);
                    
                    addedIndicesSize+=3;
                    
                    return vertices[int(indices[i * 3])];
                    break;
                    
                case OF_PRIMITIVE_LINE_LOOP:
                    mesh.addVertex(vertices[i]);
                    mesh.addVertex(vertices[i + 1]);
                    mesh.addVertex(vertices[i + 2]);
                    
                    addedIndicesSize+=3;
                    
                    return vertices[i * 3];
                    break;
                default:
                    return vertices[0];
                    break;
            }
        }
    };

    ModelDrawer(){
        verticesSize = 0;
        indicesSize = 0;
        addedIndicesSize = 0;
        mesh.clear();
        mesh.enableIndices();
        primitiveMode = OF_PRIMITIVE_TRIANGLES;
        indices = *new vector<ofIndexType>(MAX_INDICES);
    };
};
#endif
