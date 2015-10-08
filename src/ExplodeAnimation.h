//
//  ExplodeAnimation.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/08.
//
//

#ifndef __mauInteractive__ExplodeAnimation__
#define __mauInteractive__ExplodeAnimation__

#include "ofMain.h"
#include "ParticleElement.h"
#include "ParticleConnection.h"
#include "TriangleConnection.h"

#define DEFAULT_PARTICLE_NUM 15
#define DEFAULT_SPEED_RANGE 5


class ExplodeAnimation{
private:
    ofVec2f position;
    vector<ParticleElement> particles;
    float speed_range = DEFAULT_SPEED_RANGE;
    ofColor color = ofColor(0,255,0,100);
    
    vector<ParticleConnection> connections;
    vector<TriangleConnection> triangleconnections;
    
    ofVec2f speed_generator(float range);
    
public:
    void set_color(ofColor color);
    void set_position(ofVec2f pos);
    void set_speed_range(float range);
    void init();
    void update();
    void draw();
};

#endif /* defined(__mauInteractive__ExplodeAnimation__) */
