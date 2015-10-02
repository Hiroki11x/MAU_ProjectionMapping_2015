//
//  UserAgents.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/30.
//
//
#ifndef UserAgents_h
#define UserAgents_h

#define COLOR_MAX 255

#include "SceneElement.h"
#include "ofMain.h"
#include "UserAgent.h"
#include "Connection.h"
#include "MatrixGenerator.h"

class UserAgents : public SceneElement {
public:
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    virtual void onMouseDown(int x,int y) override;
    
    UserAgents(){};
    
private:
    MatrixGenerator matrix_generator;
    
    vector<Connection *> connections;
    vector<UserAgent *> userAgentArray;
    int userAgentsSize;
    int connectionSize;
    void addAgent(ofVec2f position);
    void addConnection(int startIndex,int endIndex,float duration);
    int  getUserAgentSize();
    int  getConnectionSize();
    void setup_user_agent();
};
#endif
