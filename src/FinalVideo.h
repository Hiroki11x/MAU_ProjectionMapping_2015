//
//  FinalVideo.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#ifndef __mauInteractive__FinalVideo__
#define __mauInteractive__FinalVideo__

#include "SceneElement.h"
#include "ofMain.h"

class FinalVideo : public SceneElement {
    
private:
    ofVideoPlayer video;
public:
    virtual void reset() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    FinalVideo(){};
};

#endif /* defined(__mauInteractive__FinalVideo__) */
