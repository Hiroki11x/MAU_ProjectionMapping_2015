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
#define GENE_X_NUM 8
#define GENE_Y_NUM 12

#define USER_CIRCLE_SIZE 10

#include "SceneElement.h"
#include "ofMain.h"
#include "UserAgent.h"
#include "Connection.h"
#include "MatrixGenerator.h"
#include "FadeBackgroundUtil.h"
#include "StrechyRectSwiper.h"
#include "AlphaSwiper.h"
#include "ofxSuperLogUtil.h"
//#include "GraphLog.h"
#include "ExplodeAnimation.h"
#include "JsonReceiver.h"
#include "JsonImageReceiveThread.h"

class UserAgents : public SceneElement {
public:
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    UserAgents(){};
private:
    FadeBackgroundUtil back_animation;
    StrechyRectSwiper strechyRectSwiper;
    AlphaSwiper alphaSwiper;
    ofxSuperLogUtil superLogUtil;
//    GraphLog graphLog;
    MatrixGenerator matrix_generator;
    
    vector<Connection *> connections;
    vector<UserAgent *> userAgentArray;
    int userAgentsSize;
    int connectionSize;
    
    vector<ExplodeAnimation> explodeanimations;
    void createExplodeAnimation(ofVec2f pos);
    
    void addConnection(int startIndex,int endIndex,float duration);
    int  getUserAgentSize();
    int  getConnectionSize();
    void setup_user_agent();
    
    void check_is_json_new();
    void addAgent(int add_num);
    ofVec3f select_position();
    
    int json_num;
    
    void check_agent_size(int delete_adder);
};
#endif
