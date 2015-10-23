//
//  InitialVideoSceneManager.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#ifndef __mauInteractive__InitialVideoSceneManager__
#define __mauInteractive__InitialVideoSceneManager__

#include "SceneManager.h"
#include "InitialVideo.h"


class InitialVideoSceneManager : public SceneManager {
public:
    
    virtual void reset() override;
    virtual void setup() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
};

#endif /* defined(__mauInteractive__InitialVideoSceneManager__) */
