//
//  UsersManager.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/30.
//
//


#include "ofMain.h"
#include "SceneManager.h"
#include "SceneElement.h"

#include "SceneManager.h"
#include "UserAgents.h"
#include "AgentAnalyze.h"
#include "SingleAgentAnalyze.h"



class UserAgentsSceneManager : public SceneManager {
public:
    virtual void setup() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    virtual bool nextElement() override;
};
