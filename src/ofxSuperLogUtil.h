//
//  ofxSuperLogUtil.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/05.
//
//
//  void ofxSuperLogDisplay::draw(ofEventArgs &e)
//  の色とかを結構いじった
//
//  void ofxSuperLogDisplay::log(ofLogLevel level, const string & module, const string & message)
//  もいじった、コメントアウトしてある
//

#ifndef __mauInteractive__ofxSuperLogUtil__
#define __mauInteractive__ofxSuperLogUtil__

#include <stdio.h>
#include "ofxSuperLog.h"

class ofxSuperLogUtil{
private:
public:
    void init();
    void set_log(string tag, float arg);
};

#endif /* defined(__mauInteractive__ofxSuperLogUtil__) */
