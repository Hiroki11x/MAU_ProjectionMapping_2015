//
//  AgentCircle.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/09.
//
//

#ifndef __mauInteractive__AgentCircle__
#define __mauInteractive__AgentCircle__

#include "ofMain.h"
#include "FontManager.h"

class AgentCircle{
    
private:
    
    float line_y1 = ofGetHeight()/2;
    float line_y2 = 3*ofGetHeight()/2;
    
    float size;
    float multiple_of_size;
    float line_length;
    
    string id;
    string username;
    wstring text;//つぶやいた内容(これだけ["user"]内ではない)
    int friends_count;//フォローしてるアカウント数
    int statuses_count;//つぶやいてる数
    int followers_count;
    float registertime;

    
public:
    ofVec2f position;
    AgentCircle(){};
    
    void set_position(ofVec2f _pos);
    
    void update();
    void draw_line(float x, float y);
    void init();
    
    void get_info_from_twitter(string name,string id, wstring text,int friends_count,int statuses_count,int followers_count);//twitterからの取得情報を書く
};

#endif /* defined(__mauInteractive__AgentCircle__) */
