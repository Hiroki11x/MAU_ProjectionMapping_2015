//
//  ofxTweenUtil.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/04.
//
//


#include "ofMain.h"
#include "ofxTween.h"

class ofxTweenUtil{
private:
    unsigned delay = 0;
    unsigned duration = 1000;
    
    void draw();
public:
    void setup();
    void init();
    
    void update();
    
    float get_update_value();
    
    void set_delay(unsigned int delay);
    void set_duration(unsigned int duration);
    
    //    ofxTween tweencubic;
    //    ofxEasingCubic 	easingcubic;
    
    ofxTween tweenlinear;
    ofxEasingLinear elasticlinnear;
    
};
