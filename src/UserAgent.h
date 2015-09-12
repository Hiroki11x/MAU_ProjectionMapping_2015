//
//  UserAgent.h
//  MauInteractive
//
//  Created by HirokiNaganuma on 2015/09/12.
//
//

#ifndef MauInteractive_UserAgent_h
#define MauInteractive_UserAgent_h

#include "ofMain.h"
class UserAgent{
public:
    ofVec2f position;
    float size;
    float multiple_of_size;
    
    ofImage icon;
    string id;
    string username;
    float registertime;
    
    ofColor color;
    
    UserAgent(){};
    
    void set_position(ofVec2f _pos);
    void set_size(float _size);
    void set_color(ofColor _color);
    
    void update();
    void draw();
    void init();
    
    void get_info_from_twitter();//twitterからの取得情報を書く
};

#endif
