//
//  UtVj.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#ifndef __mauInteractive__UtVj__
#define __mauInteractive__UtVj__

#include "ofMain.h"

#define MAX 100

class UtVj{
public:
    void reset();
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
private:
    ofCamera cam;
    float count;
    ofLight light;
    int term = 0;
    int offset = 0;
};

#endif /* defined(__mauInteractive__UtVj__) */
