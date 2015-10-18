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
#include "JsonReceiver.h"
#include "ShiseidoLifeClock.h"
#include "SingleUserManager.h"

class SingleAgentAnalyze : public SceneElement {
    
private:
    int max_row ;
    int max_column ;
    
    bool mode = false;
    
    void check_is_json_new();
    void addAgent(int add_num);
    
    int json_num;
    ShiseidoLifeClock shiseido;
    
public:

    virtual void reset() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    SingleAgentAnalyze(){};
};

#endif /* defined(__mauInteractive__SingleAgentAnalyze__) */
