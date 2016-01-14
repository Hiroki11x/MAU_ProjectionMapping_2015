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
    void draw();
    void update();
    int switch_mode();
    ofEasyCam cam;
    void set_line_num(int num);
    void add_line_num(int add);
private:
    int line_num;
    static int json_num;
    int mode = 1;
    ofPath path;
    float max_angle;
    vector<ofVec2f> vec;
    vector<string> userNames;
    ofMesh mesh;
    void draw_bezier_map();
    void draw_bezier_web();
    void draw_mesh();
    void draw_default_circle();
    void draw_bezier_circle();
};

#endif /* defined(__mauInteractive__ShiseidoLifeClock__) */
