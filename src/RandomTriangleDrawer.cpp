//
//  RandomTriangleDrawer.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/07.
//
//

#include "RandomTriangleDrawer.h"

void RandomTriangleDrawer::changeMesh(int num, int cNum){
    mesh.clear();
    for(int i = 0; i < num; i++){
        mesh.addVertex(vertices.at(ofRandom(vertices.size())));
    }
    coloredMesh.clear();
    for(int i = 0; i < cNum; i++){
        coloredMesh.addVertex(vertices.at(ofRandom(vertices.size())));
    }
}

void RandomTriangleDrawer::drawTriangleMesh(){

    ofPushStyle();
    glPointSize(10.0);
    ofSetColor(rtColor);
    mesh.draw(OF_MESH_POINTS);
    mesh.draw(OF_MESH_WIREFRAME);
    ofSetColor(rtTransColor);
    coloredMesh.draw(OF_MESH_POINTS);
    coloredMesh.draw(OF_MESH_FILL);
    ofPopStyle();
}

void RandomTriangleDrawer::setVertices(vector<ofVec3f> newVec, float size){
    for(int i = 0; i < newVec.size(); i++){
        vertices.push_back(newVec.at(i) * size);
    }
}