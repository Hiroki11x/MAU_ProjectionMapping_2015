//
//  ofxAssimpModelLoaderextend.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/30.
//
//

#ifndef ofxAssimpModelLoaderextend_h
#define ofxAssimpModelLoaderextend_h

#include "ofxAssimpModelLoader.h"

class ofxAssimpModelLoaderExtend : public ofxAssimpModelLoader{
public:
    int meshNum[4] = {0,0,0,0};
    int showMeshIndex[4] = {0,0,0,0};
    int modelMeshNum[4] = {2970,72,8247,3354};
    int spentFrame = 0;
    
    void draw(ofPolyRenderMode renderType);
    void addMesh();
    void changeRange();
};
#endif
