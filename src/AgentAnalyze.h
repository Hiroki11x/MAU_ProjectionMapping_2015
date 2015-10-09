//
//  AgentAnalyze.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/09.
//
//

#ifndef __mauInteractive__AgentAnalyze__
#define __mauInteractive__AgentAnalyze__

#include "SceneElement.h"
#include "ofMain.h"

#include "JsonReceiver.h"

class AgentAnalyze : public SceneElement {
    
private:
    
    void createExplodeAnimation(ofVec2f pos);
    
    int  getUserAgentSize();
    
    void check_is_json_new();
    void addAgent(int add_num);
    
    int json_num;
    
public:
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    AgentAnalyze(){};
};

#endif /* defined(__mauInteractive__AgentAnalyze__) */
