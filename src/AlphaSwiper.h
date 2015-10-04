//
//  AlphaSwiper.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/04.
//
//

#ifndef __mauInteractive__AlphaSwiper__
#define __mauInteractive__AlphaSwiper__

#include "ofMain.h"
#include "ofxTweenUtil.h"

class AlphaSwiper{
private:
    ofxTweenUtil TweenUtil;
    
public:
    void init();
    void update();
    void draw();
};

#endif /* defined(__mauInteractive__AlphaSwiper__) */
