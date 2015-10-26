//
//  StartVideo.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/24.
//
//

#ifndef StartVideo_h
#define StartVideo_h

#include "ofMain.h"
#include "SceneElement.h"
class StartVideo : public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    virtual void stop() override;
    
    ofVideoPlayer vPlayer;
    bool isPlaying;
    ofImage waitImage;
    bool isStarted;
};
#endif