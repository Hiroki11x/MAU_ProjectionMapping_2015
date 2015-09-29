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
    
    int meshNum = 0;
    virtual void draw(ofPolyRenderMode renderType) override;
    
    void addMesh();

};
#endif /* ofxAssimpModelLoaderextend_hpp */
