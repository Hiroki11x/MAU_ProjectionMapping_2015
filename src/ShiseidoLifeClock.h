//
//  ShiseidoLifeClock.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/12.
//
//

#ifndef __mauInteractive__ShiseidoLifeClock__
#define __mauInteractive__ShiseidoLifeClock__

#include "ofMain.h"

class ShiseidoLifeClock{
public:
    void init();
    void draw();
    void update();
private:
    ofPath path;
    float max_angle;
    float start_time;
};

#endif /* defined(__mauInteractive__ShiseidoLifeClock__) */
