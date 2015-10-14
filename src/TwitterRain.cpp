//
//  TwitterRain.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/08.
//
//
#include "TwitterRain.h"

void TwitterRain::init(){
    
    tweets = *new vector<Tweet>;
    align = UL2_TEXT_ALIGN_V_TOP|UL2_TEXT_ALIGN_CENTER;
    strAlign="top-center [8]";
    strDirection="Left to Right (TTB)";
    glCullFace(GL_BACK);//裏面をカリング
    glEnable(GL_DEPTH_TEST);
    bRotation=false;
    font.loadFont("Arial.ttf", 10);
    font.loadFont("Yumin Demibold",32,true,true,0.3f,0,true)||font.loadSubFont("YuMincho");
    font.loadSubFont(OF_TTF_SERIF,1.2,-0.02);
    font.loadSubFont("Geeza Pro",1,-0.04,0x0600,0x06FF,"arab");
    font.useProportional(true);
    font.useVrt2Layout(true);
    font.setLineHeight(font.getFontSize()*1.5);
}

void TwitterRain::draw(){
    ofSetColor(255);
    int w,h,x,y;
    x=100;
    y=100;
    w=mouseX-x;
    h=mouseY-y;
    glPushMatrix();{
        light.enable();
        light.setPosition(ofGetWidth()*.5,ofGetHeight()*.5,ofGetWidth());
        for(int i = 0; i < tweets.size(); i++){
            glPushMatrix();
            if(bRotation){
                ofSetColor(25,255,25,tweets.at(i).alpha);
                ofRectangle rc= font.getStringBoundingBox(tweets.at(i).tweetInfo,x,y,w,h,align);
                glTranslatef(tweets.at(i).position.x, tweets.at(i).position.y, tweets.at(i).position.z);
                glRotatef(ofGetElapsedTimef()*tweets.at(i).rotateSpeed, 0, 1, 0);
                glTranslatef(x-rc.x -rc.width*.5,0,0);
                font.drawString(tweets.at(i).tweetInfo,0,0);
            }else{
                ofSetColor(25,255,25,tweets.at(i).alpha);
                font.drawString(tweets.at(i).tweetInfo, tweets.at(i).position.x, tweets.at(i).position.y);
            }
            glPopMatrix();
        }
        light.disable();
        glDisable(GL_LIGHTING);
    }glPopMatrix();
}

void TwitterRain::update(){

    for(int i = 0; i < tweets.size(); i++){
        tweets.at(i).position.y += tweets.at(i).downSpeed;
        if(tweets.at(i).position.y < ofGetHeight()) continue;
        tweets.erase(tweets.begin() + i);
        i--;
    }
    spentFrames++;
    if(!(spentFrames % 7 == 0)) return;
    if(!(tweets.size() < DISPLAY_TWEET_NUM)) return;
    if(!(JsonReceiver::getInstance().updateNum > 0)) return;
    wstring twi;
    twi.append(JsonReceiver::getInstance().getRandomTweetInfo().text);
    tweets.push_back((Tweet){twi,ofVec3f(ofRandom(-200,1024),-100,ofRandom(-200, 200)),ofRandom(-30,30),ofRandom(8,15),ofRandom(100,255)});
}

void TwitterRain::onMouseDown(int x, int y){
    mouseX = x;
    mouseY = y;
}

void TwitterRain::keyPressed(int key){
    switch (key) {
        case 'r':
            bRotation = !bRotation;
            break;
        case 'R':
            init();
        default:
            break;
    }
}
