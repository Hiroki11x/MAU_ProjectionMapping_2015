//
//  ParticleConnection.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/08.
//
//

#include "ParticleConnection.h"

void ParticleConnection::set_node(ofVec2f* start, ofVec2f* end){
    start_pos = start;
    end_pos = end;
}


void ParticleConnection::init(){
    
}
void ParticleConnection::draw(){
    //    ofSetColor(255);
    ofLine(*start_pos, *end_pos);
}