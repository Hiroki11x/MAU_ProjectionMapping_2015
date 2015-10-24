//
//  EndingVideo.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/23.
//
//

#ifndef EndingVideo_h
#define EndingVideo_h

#include "ofMain.h"
#include "SceneElement.h"
class EndingVideo : public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    virtual void stop() override;
    
    ofVideoPlayer vPlayer;
    bool isPlaying;
};
#endif