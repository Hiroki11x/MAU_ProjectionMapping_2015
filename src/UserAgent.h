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
    string text;//つぶやいた内容(これだけ["user"]内ではない)
    int friends_count;//フォローしてるアカウント数
    int statuses_count;//つぶやいてる数
    int followers_count;
    float registertime;
    
    ofColor color;
    ofxTrueTypeFontUC font,smallfont;
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
    
    void get_info_from_twitter(string name,string id, string text,int friends_count,int statuses_count,int followers_count, ofImage image);//twitterからの取得情報を書く
};

#endif
