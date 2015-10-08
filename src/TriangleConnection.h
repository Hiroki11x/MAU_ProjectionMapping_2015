//
//  TriangleConnection.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/08.
//
//

#ifndef __mauInteractive__TriangleConnection__
#define __mauInteractive__TriangleConnection__

#include "ofMain.h"

class TriangleConnection{
private:
    ofVec2f* pos1;
    ofVec2f* pos2;
    ofVec2f* pos3;
    ofColor color;
public:
    void set_color(ofColor arg_color);
    void set_3_pos(ofVec2f* pos1, ofVec2f* pos2,ofVec2f* pos3);
    void init();
    void draw();
};


#endif /* defined(__mauInteractive__TriangleConnection__) */
