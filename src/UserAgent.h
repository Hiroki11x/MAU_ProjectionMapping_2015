//
//  UserAgent.h
//  MauInteractive
//
//  Created by HirokiNaganuma on 2015/09/12.
//
//

#ifndef MauInteractive_UserAgent_h
#define MauInteractive_UserAgent_h

#define DEFAULT_USER_CIRCLE_SIZE 3
#define INNER_CIRCLE_MAGNIFICATION 0.75

#define MIN_CIRCLE_MAGNIFICATION 1.2
#define MAX_CIRCLE_MAGNIFICATION 1.7

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"


class UserAgent{
private:
    
    float size;
    float multiple_of_size;
    float line_length;
    
    ofImage icon;
    string id;
    string username;
    float registertime;
    
    ofColor color;
    ofxTrueTypeFontUC font;
public:
    ofVec2f position;
    UserAgent(){};
    
//    void set_user_id(string id);
//    void set_user_name(string name);
    
    void set_position(ofVec2f _pos);
    void set_size(float _size);
    void set_color(ofColor _color);
    void calc_line_length();
    
    void update();
    void draw();
    void init();
    
    void get_info_from_twitter(string name,string id, ofImage image);//twitterからの取得情報を書く
};

#endif
