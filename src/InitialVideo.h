//
//  InitialVideo.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#ifndef __mauInteractive__InitialVideo__
#define __mauInteractive__InitialVideo__

#include "SceneElement.h"
#include "ofMain.h"

class InitialVideo : public SceneElement {
    
private:
    ofVideoPlayer video;
    ofImage img;
public:
    virtual void reset() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    InitialVideo(){};
};

#endif /* defined(__mauInteractive__InitialVideo__) */
