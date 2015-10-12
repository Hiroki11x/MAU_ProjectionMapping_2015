//
//  SingleAgentAnalyze.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/12.
//
//

#ifndef __mauInteractive__SingleAgentAnalyze__
#define __mauInteractive__SingleAgentAnalyze__

#include "SceneElement.h"
#include "ofMain.h"
#include "SingleAgent.h"
#include "JsonReceiver.h"

class SingleAgentAnalyze : public SceneElement {
    
private:
    void check_is_json_new();
    void addAgent(int add_num);
    
    int json_num;
    
    vector<SingleAgent> user_agent;
    
public:
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    SingleAgentAnalyze(){};
};

#endif /* defined(__mauInteractive__SingleAgentAnalyze__) */
