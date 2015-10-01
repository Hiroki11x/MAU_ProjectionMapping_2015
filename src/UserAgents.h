//
//  UserAgents.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/30.
//
//
#ifndef UserAgents_h
#define UserAgents_h

#include "SceneElement.h"
#include "ofMain.h"

class UserAgents : public SceneElement {
public:
    float connections[100][100];

    vector<ofVec3f> userAgentPositions;
    
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    virtual void onMouseDown(int x,int y) override;
    
    UserAgents(){};
};
#endif
