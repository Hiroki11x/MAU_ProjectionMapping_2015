//
//  AgentCircle.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/09.
//
//

#ifndef __mauInteractive__AgentCircle__
#define __mauInteractive__AgentCircle__

#define DEFAULT_USER_CIRCLE_SIZE 300
#define INNER_CIRCLE_MAGNIFICATION 0.75

#define MIN_CIRCLE_MAGNIFICATION 1.2
#define MAX_CIRCLE_MAGNIFICATION 1.7

#include "ofMain.h"
#include "FontManager.h"

class AgentCircle{
    
private:
    
    float line_y1 = ofGetHeight()/2;
    float line_y2 = 3*ofGetHeight()/2;
    
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
    
public:
    ofVec2f position;
    AgentCircle(){};
    
    void set_position(ofVec2f _pos);
    void set_size(float _size);
    void set_color(ofColor _color);
    
    void update();
    void draw_circle();
    void draw_line(float line_x);
    void init();
    
    void get_info_from_twitter(string name,string id, string text,int friends_count,int statuses_count,int followers_count, ofImage image);//twitterからの取得情報を書く
};

#endif /* defined(__mauInteractive__AgentCircle__) */
