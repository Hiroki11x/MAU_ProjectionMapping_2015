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
#include "FontManager.h"


class UserAgent{
private:
    
    int generater_index;
    
    float line_y1 = ofGetHeight()/2;
    float line_y2 = 3*ofGetHeight()/2;
    
    float size;
    float multiple_of_size;
    float line_length;
    
    ofImage icon;
    string id;
    string username;
    wstring text;//つぶやいた内容(これだけ["user"]内ではない)
    int friends_count;//フォローしてるアカウント数
    int statuses_count;//つぶやいてる数
    int followers_count;
    float registertime;
    
    ofColor color;
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
    
    void get_info_from_twitter(string name,string id, wstring text,int friends_count,int statuses_count,int followers_count, ofImage image);//twitterからの取得情報を書く
    
    void set_generater_index(int index);
    int get_generater_index();
    
    void draw_line(float line_x);
    void draw_circle();
    
    
};

#endif
