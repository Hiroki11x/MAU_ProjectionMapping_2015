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

    void changeMesh(int num, int cNum);
    void drawTriangleMesh();
    void setVertices(vector<ofVec3f> newVec, float size);
};
#endif