//
//  TwitterRain.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/08.
//
//
#ifndef TwitterRain_h
#define TwitterRain_h

#include "ofMain.h"
#include "SceneElement.h"
#include "ofx3DFont.h"
#include "JsonReceiver.h"


#define DISPLAY_TWEET_NUM 20

class TwitterRain : public SceneElement {
public:
    
    struct Tweet{
        wstring tweetInfo;
        ofVec3f position;
        float rotateSpeed;
        float downSpeed;
    };
    
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    
    wstring convToWString(string src);
    template <class T>
    wstring convToUCS4(basic_string<T> src);
    
    ofx3DFont font;
    vector<Tweet> tweets;
    wstring show;
    string strAlign;
    string strDirection;
    bool renderingMode;
    bool bRotation;
    int align;
    int mouseX;
    int mouseY;
    int z;
    bool tweetDebug;
    ofLight light;
};
#endif
