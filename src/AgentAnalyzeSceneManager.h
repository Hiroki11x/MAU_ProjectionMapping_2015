//
//  AgentAnalyzeSceneManager.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/09.
//
//

#ifndef __mauInteractive__AgentAnalyzeSceneManager__
#define __mauInteractive__AgentAnalyzeSceneManager__

#include "SceneManager.h"
#include "UserAgents.h"

class AgentAnalyzeSceneManager : public SceneManager {
public:
    virtual void setup() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
};


#endif /* defined(__mauInteractive__AgentAnalyzeSceneManager__) */
