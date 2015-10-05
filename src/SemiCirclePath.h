//
//  SemiCirclePath.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/04.
//

#include "ofMain.h"

class SemiCirclePath{
private:
    ofPath green_path;
    ofPath black_path;
    int div_num;
    ofColor color;
    float width;
    bool mode;
    
public:
    void init();
    void draw(float radius);
    void set_width(float width);
    void set_color(ofColor color);
    void set_div_num(int div_num);
    void set_rotate_mode(bool mode);
};
