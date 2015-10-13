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
    static float start_time;
    void init();
    void draw();
    void update();
    void switch_mode();
private:
    int mode = 1;
    ofPath path;
    float max_angle;
    vector<ofVec2f> vec;
    void draw_default_circle();
    void draw_bezier_map();
};

#endif /* defined(__mauInteractive__ShiseidoLifeClock__) */
