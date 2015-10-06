//
//  3DModelDrawer.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/01.
//
//
#include "ModelDrawer.h"

ofVec3f ModelDrawer::addVertex(int i){
    if(i < MAX_INDICES/3 - 1 && i < indicesSize/3 - 1){
 
        mesh.addVertex(vertices[int(indices[i * 3])]);
        mesh.addVertex(vertices[int(indices[i * 3 + 1])]);
        mesh.addVertex(vertices[int(indices[i * 3 + 2])]);
        
        mesh.addIndex(i * 3);
        mesh.addIndex(i * 3 + 1);
        mesh.addIndex(i * 3 + 2);
        
        addedIndicesSize+=3;
        
        return vertices[int(indices[i * 3])];
    }
}

void ModelDrawer::changeColoredMode(ColoredMeshMode mode){
    if(mode == AFFECTED_GLAVITY_GLASS) grassFrames = 0;
    coloredMeshMode = mode;
}

void ModelDrawer::changeColoredPartMesh(){
    if(coloredMeshMode != AFFECTED_GLAVITY_GLASS) coloredPartMesh.clear();
    coloredMeshSize = 0;
    coloredIndex+=10;
    for(int i = 0; i < (float)addedIndicesSize / 300.0 * COLORED_MESH_PER_HANDRED_TRIANGLE; i++){
        int index;
        
        switch (coloredMeshMode) {
            case LINE:
                if(i + coloredIndex >= addedIndicesSize/3.0){
                    coloredIndex = 0;
                }
                index = i + coloredIndex;
                break;
                
            case RANDOM:
            case AFFECTED_GLAVITY_GLASS:
                index = ofRandom(0, addedIndicesSize/3);
                break;
                
            default:
                return;
        }
        
        coloredMeshesVec[i * 3]     = vertices[int(indices[index * 3])];
        coloredMeshesVec[i * 3 + 1] = vertices[int(indices[index * 3 + 1])];
        coloredMeshesVec[i * 3 + 2] = vertices[int(indices[index * 3 + 2])];
        
        coloredPartMesh.addVertex(coloredMeshesVec[i * 3]);
        coloredPartMesh.addVertex(coloredMeshesVec[i * 3 + 1]);
        coloredPartMesh.addVertex(coloredMeshesVec[i * 3 + 2]);
        
        coloredMeshSize++;
    }
}

void ModelDrawer::drawColoredMesh(){
    
    if(coloredMeshMode == AFFECTED_GLAVITY_GLASS){
        ofPushMatrix();
        ofTranslate(ofPoint(0, -grassFrames * 6.0, 0));
        coloredPartMesh.draw(ofPolyRenderMode::OF_MESH_FILL);
        ofPopMatrix();
        return;
    }
    coloredPartMesh.draw(ofPolyRenderMode::OF_MESH_FILL);
}

void ModelDrawer::drawModel(float scale, bool fill){
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

void ModelDrawer::drawPercentage(){
    ofNoFill();
    ofRect(50, 50, 400, 35);
    ofFill();
    ofRect(50, 50, 400 * (float(addedIndicesSize) / float(indicesSize)), 35);
}

void ModelDrawer::setPrimitiveMode(ofPrimitiveMode primitiveMode){
    this->primitiveMode = primitiveMode;
}

void ModelDrawer::setVertices(vector<ofVec3f> newVec, vector<ofIndexType> newIndices,float size){
    
    int preSize = verticesSize;
    verticesSize += newVec.size();
    for(int i = 0; i < newVec.size(); i++){
        if(i + preSize > MAX_VERTICES - 1){break;}
        vertices[i + preSize] = newVec.at(i) * size;
    }
    
    int preIndiceSize = indicesSize;
    indicesSize += newIndices.size();
    for(int i = 0; i < newIndices.size(); i++){
        if(i + preIndiceSize > MAX_INDICES - 1){break;}
        indices[i + preIndiceSize] = newIndices.at(i) + preSize;
    }
}

void ModelDrawer::updateColoredMesh(float size){

    switch (coloredMeshMode) {
        case LINE:
        case RANDOM:
            for(int i = 0; i < coloredMeshSize; i++){
                coloredPartMesh.setVertex(3 * i    , coloredMeshesVec[3 * i] * size);
                coloredPartMesh.setVertex(3 * i + 1, coloredMeshesVec[3 * i + 1] * size);
                coloredPartMesh.setVertex(3 * i + 2, coloredMeshesVec[3 * i + 2] * size);
                coloredPartMesh.addColor(ofColor(ofRandom(255),255,ofRandom(255),ofRandom(255)));
            }
            break;
            
        case AFFECTED_GLAVITY_GLASS:
            grassFrames++;
            if(grassFrames > 40) changeColoredMode(LINE);
            if(grassFrames > 20){
                return;
            }
            for(int i = 0; i < coloredMeshSize; i++){
                coloredPartMesh.setVertex(3 * i    , coloredMeshesVec[3 * i]     * size * grassFrames / 3.0);
                coloredPartMesh.setVertex(3 * i + 1, coloredMeshesVec[3 * i + 1] * size * grassFrames / 3.0);
                coloredPartMesh.setVertex(3 * i + 2, coloredMeshesVec[3 * i + 2] * size * grassFrames / 3.0);
            }
        default:
            break;
    }
}

ModelDrawer::ModelDrawer(){
    verticesSize = 0;
    indicesSize = 0;
    addedIndicesSize = 0;
    mesh.clear();
    mesh.enableIndices();
    coloredPartMesh.enableColors();
    primitiveMode = OF_PRIMITIVE_TRIANGLES;
    indices = *new vector<ofIndexType>(MAX_INDICES);
}