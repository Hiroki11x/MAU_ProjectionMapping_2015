//
//  AgentAnalyze.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/09.
//
//

#ifndef __mauInteractive__AgentAnalyze__
#define __mauInteractive__AgentAnalyze__

#define COLOR_MAX 255
#define GENE_X_NUM 12
#define GENE_Y_NUM 18

#define USER_CIRCLE_SIZE 10

#include "SceneElement.h"
#include "ofMain.h"
#include "AgentCircle.h"
#include "JsonReceiver.h"

class AgentAnalyze : public SceneElement {
    
private:
    void check_is_json_new();
    void addAgent(int add_num);
    
    int index;
    int json_num;
    
    vector<AgentCircle> agent_circles;
    
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
