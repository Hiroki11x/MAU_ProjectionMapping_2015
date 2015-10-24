//
//  FinalVideoSceneManager.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#ifndef __mauInteractive__FinalVideoSceneManager__
#define __mauInteractive__FinalVideoSceneManager__

#include "SceneManager.h"
#include "FinalVideo.h"

class FinalVideoSceneManager : public SceneManager {
public:
    
    virtual void reset() override;
    virtual void setup() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
};

#endif /* defined(__mauInteractive__FinalVideoSceneManager__) */
