//
//  SpyMesh.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//

#ifndef SpyMesh_h
#define SpyMesh_h

#include "ofMain.h"
#include "SceneElement.h"
#include "TrianglePoints.h"
#include "LinePoints.h"

#define NUM_BALL 80

class SpyMesh : public SceneElement {
public:
    
    vector<ofPoint> ps;
    vector<TrianglePoints> ts;
    ofImage spyImage;
    unsigned char * spyData;
    //int imgW,imgH;
    vector<ofColor *> spyColors;
    
    Boolean DetDelaunay(const ofPoint& p0,const ofPoint& p1,const ofPoint& p2,const ofPoint& p3);
    int index;
    void generate(float x, float y);
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    virtual void onMouseDown(int x,int y) override;
    
};

#endif
