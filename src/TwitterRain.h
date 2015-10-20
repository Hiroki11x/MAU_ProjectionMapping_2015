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
#include "ofxTrueTypeFontUL2.h"

#define DISPLAY_TWEET_NUM 20

class TwitterRain : public SceneElement {
public:
    struct Tweet{
        wstring tweetInfo;
        ofVec3f position;
        float rotateSpeed;
        float downSpeed;
        int alpha;
        ofColor c;
        bool visible;
    };
    
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    void reset();
    void putDammyData();
    
    int align;
    int mouseX;
    int mouseY;
    int spentFrames;
    int tweetNum;
    bool bRotation;
    bool drawCircuitMode = false;
    bool putDammyText;
    
    vector<Tweet> tweets;
    wstring show;
    string strAlign;
    string strDirection;

    ofLight light;
    ofxTrueTypeFontUL2 font;
    ofShader backShader;
};
#endif
