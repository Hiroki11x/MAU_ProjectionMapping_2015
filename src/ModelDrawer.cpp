//
//  3DModelDrawer.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/01.
//
//
#include "ModelDrawer.h"

void ModelDrawer::drawPercentage(){
    ofNoFill();
    ofRect(50, 50, 400, 35);
    ofFill();
    ofRect(50, 50, 400 * (float(addedIndicesSize) / float(indicesSize)), 35);
}

void ModelDrawer::setPrimitiveMode(ofPrimitiveMode primitiveMode){
    this->primitiveMode = primitiveMode;
}

void ModelDrawer::changeColoredPartMesh(){
    coloredPartMesh.clear();
    coloredMeshSize = 0;
    for(int i = 0; i < (float)addedIndicesSize / 300.0 * COLORED_MESH_PER_HANDRED_TRIANGLE; i++){
        
        int index = ofRandom(0,addedIndicesSize/3);
        
        coloredMeshesVec[i * 3]     = vertices[int(indices[index * 3])];
        coloredMeshesVec[i * 3 + 1] = vertices[int(indices[index * 3 + 1])];
        coloredMeshesVec[i * 3 + 2] = vertices[int(indices[index * 3 + 2])];
        
        coloredPartMesh.addVertex(vertices[int(indices[index * 3])]);
        coloredPartMesh.addVertex(vertices[int(indices[index * 3 + 1])]);
        coloredPartMesh.addVertex(vertices[int(indices[index * 3 + 2])]);
            
        coloredPartMesh.addIndex(i * 3);
        coloredPartMesh.addIndex(i * 3 + 1);
        coloredPartMesh.addIndex(i * 3 + 2);
        
        coloredMeshSize++;
    }
}

void ModelDrawer::drawColoredMesh(){
    
    coloredPartMesh.draw(ofPolyRenderMode::OF_MESH_FILL);
}

void ModelDrawer::updateColoredMesh(float size){
    for(int i = 0; i < coloredMeshSize; i++){
       /* coloredPartMesh.setVertex(3 * i    , coloredMeshesVec[3 * i] * size);
        coloredPartMesh.setVertex(3 * i + 1, coloredMeshesVec[3 * i + 1] * size);
        coloredPartMesh.setVertex(3 * i + 2, coloredMeshesVec[3 * i + 2] * size);*/
        coloredPartMesh.addColor(ofColor(50,255,50,ofRandom(255)));
    }
}
                                    


