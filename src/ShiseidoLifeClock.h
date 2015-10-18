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
#include "JsonReceiver.h"
#include "FontManager.h"
#include "SingleUserManager.h"

class ShiseidoLifeClock{
public:
    static float start_time;
    
    void reset();
    void init();
    void draw(int num);
    void update(int num);
    void switch_mode();
    ofEasyCam cam;
private:

    static int json_num;
    int mode = 1;
    ofPath path;
    float max_angle;
    vector<ofVec2f> vec;
    vector<string> userNames;
    ofMesh mesh;
    void draw_bezier_map(int num);
    void draw_bezier_web(int num);
    void draw_mesh(int num);
    void draw_default_circle();
    void draw_bezier_circle(int num);
};

#endif /* defined(__mauInteractive__ShiseidoLifeClock__) */
