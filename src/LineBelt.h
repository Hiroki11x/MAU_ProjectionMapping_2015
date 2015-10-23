//
//  LineBelt.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/23.
//
//

#ifndef __mauInteractive__LineBelt__
#define __mauInteractive__LineBelt__

#include "JsonReceiver.h"
#include "ofMain.h"
#include "FontManager.h"
#include "SingleUserManager.h"

class LineBelt{
private:
    
    vector<float> position;
    vector<ofColor> color;
    float pos_center_y;
    float line_num;
    float line_length;
    bool mode;
    int mouse_x;
    
    void set_center_y(float y);
    void generate_position();
    void generate_color();
    void set_line_num(int line_num);
    void set_line_length(float line_length);
public:
    LineBelt(){};
    void reset_belt();
    void set_mode();
    void add_line_num(int add);
    void setup_belt(int num);
    void update_belt();
    void draw_belt();
    void mouseMoved(int x, int y);
};

#endif /* defined(__mauInteractive__LineBelt__) */
