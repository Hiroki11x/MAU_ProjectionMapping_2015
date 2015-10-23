//
//  LoadingVideo.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#ifndef __mauInteractive__LoadingVideo__
#define __mauInteractive__LoadingVideo__

#include "SceneElement.h"
#include "ofMain.h"
#include "ofxSuperLogUtil.h"
#include "JsonReceiver.h"
#include "SingleUserManager.h"

class LoadingVideo : public SceneElement {
    
private:
    ofVideoPlayer video,video2;
    bool mode = false;
    void check_is_json_new();
    void addAgent(int add_num);
public:
    virtual void reset() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    LoadingVideo(){};
};


#endif /* defined(__mauInteractive__LoadingVideo__) */
