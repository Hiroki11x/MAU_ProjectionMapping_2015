//
//  SingleAgentSceneManager.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/12.
//
//

#ifndef __mauInteractive__SingleAgentSceneManager__
#define __mauInteractive__SingleAgentSceneManager__

#include "SceneManager.h"
#include "SingleAgentAnalyze.h"

class SingleAgentSceneManager : public SceneManager {
public:
    virtual void reset() override;
    virtual void setup() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
};

#endif /* defined(__mauInteractive__SingleAgentSceneManager__) */
