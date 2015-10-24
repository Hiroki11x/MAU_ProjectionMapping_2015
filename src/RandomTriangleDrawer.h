//
//  RandomTriangleDrawer.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/07.
//
//

#ifndef RandomTriangleDrawer_h
#define RandomTriangleDrawer_h

#include "ofMain.h"

class RandomTriangleDrawer{
public:
    int triangleNum = 0;
    
    ofMesh mesh;
    ofMesh coloredMesh;
    vector<ofVec3f> vertices;
    //ofColor rtColor = ofColor(153,204,255, 200);//ofSetColor(50, 200, 50, 200);
    ofColor rtColor = ofColor(153,204,255, 255);//ofSetColor(50, 200, 50, 200);
    //ofColor rtTransColor = ofColor(153,204,255, 50); //ofSetColor(50, 255, 50, 50);
    ofColor rtTransColor = ofColor(153,204,255, 200); //ofSetColor(50, 255, 50, 50);

    void changeMesh(int num, int cNum);
    void drawTriangleMesh();
    void setVertices(vector<ofVec3f> newVec, float size);
};
#endif