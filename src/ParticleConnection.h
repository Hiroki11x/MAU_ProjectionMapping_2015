//
//  ParticleConnection.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/08.
//
//

#ifndef __mauInteractive__ParticleConnection__
#define __mauInteractive__ParticleConnection__

#include "ofMain.h"

class ParticleConnection{
private:
    ofVec2f* start_pos;
    ofVec2f* end_pos;
    ofColor color;
public:
    void set_node(ofVec2f* start, ofVec2f* end);
    void init();
    void draw();
};

#endif /* defined(__mauInteractive__ParticleConnection__) */
