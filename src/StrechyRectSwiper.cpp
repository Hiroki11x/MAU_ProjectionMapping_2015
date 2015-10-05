//
//  StrechyRectSwiper.cpp
//  
//
//  Created by HirokiNaganuma on 2015/10/04.
//
//

#include "StrechyRectSwiper.h"

//-------------------------------------------------------------------------------

void StrechyRectSwiper::set_mode(SwipeMode::Mode mode){
    this->mode = mode;
}

//-------------------------------------------------------------------------------

void StrechyRectSwiper::init(){
    init_path();
    TweenUtil.set_max(ofGetWidth());
    TweenUtil.set_delay(0);
    TweenUtil.set_duration(ofRandom(200,800));
    TweenUtil.init();
}

//-------------------------------------------------------------------------------

void StrechyRectSwiper::update(){
    if(TweenUtil.get_update_value()>= ofGetWidth()){
        init();
    }
}

//-------------------------------------------------------------------------------

void StrechyRectSwiper::draw(){
    float start_y = TweenUtil.get_update_value();
    ofSetColor(color, ofRandom(255));
    ofFill();
    
    switch (mode) {
        case SwipeMode::Down:
            ofRect(0,start_y-40, ofGetWidth(),20+start_y/5);
            ofRect(0,start_y-90, ofGetWidth(),20);
            break;
        case SwipeMode::Up:
            ofRect(0,ofGetHeight() - start_y, ofGetWidth(),20+start_y/5);
            ofRect(0,ofGetHeight() - start_y +50, ofGetWidth(),20);
            return ;
        case SwipeMode::SemiCircle: //SemiCirculePathを用いる
            semipath[0].draw(start_y*1.4);
            semipath[1].draw(start_y*1.2);
            semipath[2].draw(start_y);
            break;
        case SwipeMode::Right:
            ofRect(start_y*1.2-70, 0, 20, ofGetHeight());
            ofRect(start_y*1.2-20, 0, 20+start_y/8, ofGetHeight());
            break;
        case SwipeMode::Left:
            ofRect(ofGetWidth()-50-start_y*1.2, 0, 20, ofGetHeight());
            ofRect(ofGetWidth()-start_y*1.2, 0, 20+start_y/8, ofGetHeight());
            break;
        default:
            break;
    }
}

//-------------------------------------------------------------------------------

void StrechyRectSwiper::set_color(ofColor color){
    this->color = color;
    semipath[0].set_color(color);
    semipath[1].set_color(color);
    semipath[2].set_color(color);
}

//-------------------------------------------------------------------------------

void StrechyRectSwiper::init_path(){
    semipath[0].init();
    semipath[0].set_div_num(ofRandom(2,4));
    semipath[0].set_width(ofRandom(30,100));
    semipath[0].set_rotate_mode(true);
    
    semipath[1].init();
    semipath[1].set_div_num(ofRandom(2,5));
    semipath[1].set_width(ofRandom(30,100));
    semipath[0].set_rotate_mode(false);
    
    semipath[2].init();
    semipath[2].set_div_num(ofRandom(2,5));
    semipath[2].set_width(ofRandom(30,100));
    semipath[0].set_rotate_mode(true);
}

