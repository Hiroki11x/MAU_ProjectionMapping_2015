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

class SingleAgent{
    
private:
    
    float size;
    float multiple_of_size;
    
    ofImage icon;
    string id;
    string username;
    wstring text;//つぶやいた内容(これだけ["user"]内ではない)
    int friends_count;//フォローしてるアカウント数
    int statuses_count;//つぶやいてる数
    int followers_count;
    float registertime;
    ofColor color;
    
    ofPath path,path2;
public:
    string get_user_name();
    string get_user_id();
    wstring get_user_text();
    
    ofVec2f position;
    SingleAgent(){};
    void set_position(ofVec2f _pos);
    void set_size(float _size);
    void set_color(ofColor _color);
    
    void update();
    
    void draw_line(float x, float y);
    void draw_line(float x, float y,float z);
    void draw(float x, float y);
    void init();
    
    void get_info_from_twitter(string name,string id, wstring text,int friends_count,int statuses_count,int followers_count, ofImage image);//twitterからの取得情報を書く
};

#endif /* defined(__mauInteractive__SingleAgent__) */
