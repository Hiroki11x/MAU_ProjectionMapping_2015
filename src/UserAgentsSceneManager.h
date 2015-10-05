//
//  UsersManager.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/30.
//
//


#include "SceneManager.h"
#include "UserAgents.h"

class UserAgentsSceneManager : public SceneManager {
public:
    virtual void setup() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
};
