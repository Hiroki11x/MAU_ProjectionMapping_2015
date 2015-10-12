//
//  SingleAgent.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/12.
//
//

#ifndef __mauInteractive__SingleAgent__
#define __mauInteractive__SingleAgent__

#define INNER_CIRCLE_MAGNIFICATION 100
#define OUTER_CIRCLE_MAGNIFICATION 150

#include "ofMain.h"
#include "FontManager.h"
#include "ShiseidoLifeClock.h"


class SingleAgent{
    
private:
    
    ShiseidoLifeClock shiseido;
    
    float size;
    float multiple_of_size;
    
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
    SingleAgent(){};
    
    void set_position(ofVec2f _pos);
    void set_size(float _size);
    void set_color(ofColor _color);
    
    void update();
    void draw_circle(float x, float y);
    
    void draw();
    void init();
    
    void get_info_from_twitter(string name,string id, string text,int friends_count,int statuses_count,int followers_count, ofImage image);//twitterからの取得情報を書く
};

#endif /* defined(__mauInteractive__SingleAgent__) */
