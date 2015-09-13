//
//  connection.h
//  MauInteractive
//
//  Created by SakuragiYoshimasa on 2015/09/12.
//
//

#ifndef MauInteractive_UserAgentManager_h
#define MauInteractive_UserAgentManager_h

#define COLOR_MAX 255

#include "ofMain.h"
#include "UserAgent.h"
#include "Connection.h"

class UserAgentManager {
private:
    vector<Connection *> connections;
    vector<UserAgent *> userAgents;
    int userAgentsSize;
    int connectionSize;
    
public:
    void addAgent(ofVec2f position);
    void addConnection(int startIndex,int endIndex,float duration);
    void update();
    void draw();
    int  getUserAgentSize();
    int  getConnectionSize();
    
    UserAgentManager(){userAgentsSize = 0;}
};
#endif