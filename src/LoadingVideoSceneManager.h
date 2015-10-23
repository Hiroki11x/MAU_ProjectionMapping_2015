//
//  LoadingVideoSceneManager.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#ifndef __mauInteractive__LoadingVideoSceneManager__
#define __mauInteractive__LoadingVideoSceneManager__

#include "SceneManager.h"
#include "LoadingVideo.h"


class LoadingVideoSceneManager : public SceneManager {
public:
    
    virtual void reset() override;
    virtual void setup() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
};

#endif /* defined(__mauInteractive__LoadingVideoSceneManager__) */
