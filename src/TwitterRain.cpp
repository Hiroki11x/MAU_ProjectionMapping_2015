//
//  TwitterRain.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/08.
//
//
#include "TwitterRain.h"

void TwitterRain::init(){
    tweetNum = 0;
    tweets = *new vector<Tweet>(DISPLAY_TWEET_NUM);
    for(int index = 0; index < DISPLAY_TWEET_NUM; index++){
        tweets.at(index).position = ofVec3f(ofRandom(-200,1024),-100,ofRandom(-200, 200));
        tweets.at(index).rotateSpeed = ofRandom(-30,30);
        tweets.at(index).downSpeed = ofRandom(8,15);
        tweets.at(index).alpha = ofRandom(160,255);
        tweets.at(index).c = ofColor(ofRandom(0, 100), ofRandom(180, 255), ofRandom(180, 255));
    }
    align = UL2_TEXT_ALIGN_V_TOP|UL2_TEXT_ALIGN_CENTER;
    strAlign="top-center [8]";
    strDirection="Left to Right (TTB)";
    glCullFace(GL_BACK);//裏面をカリング
    glEnable(GL_DEPTH_TEST);
    bRotation=false;

    font.loadFont("Fonts/Gidole-Regular.ttf",32,true,true,0.3f,0,true);
    font.loadSubFont("Fonts/KozGoPro-Light.otf");
    font.loadSubFont("Fonts/Futura.ttc");
    font.loadSubFont("Fonts/FiraCode-Regular.otf");
    //font.loadSubFont(OF_TTF_SERIF,1.2,-0.02);
    font.loadSubFont("Geeza Pro",1,-0.04,0x0600,0x06FF,"arab");
    font.useProportional(true);
    font.useVrt2Layout(true);
    font.setLineHeight(font.getFontSize()*1.5);
}

void TwitterRain::draw(){
    ofDisableDepthTest();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    backShader.load("","shader.frag");
    backShader.begin();
    backShader.setUniform1f("u_time", ofGetElapsedTimef());
    backShader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    ofRect(0,0,ofGetWidth(), ofGetHeight());
    backShader.end();
    
    ofPushStyle();
    ofSetColor(255);
    int w,h,x,y;
    x=100;
    y=100;
    w=mouseX-x;
    h=mouseY-y;
    glPushMatrix();{
        light.enable();
        light.setPosition(ofGetWidth()*.5,ofGetHeight()*.5,ofGetWidth());
        for(int i = 0; i < DISPLAY_TWEET_NUM; i++){
            if(!tweets.at(i).visible) continue;
            glPushMatrix();
            if(bRotation){
                ofSetColor(tweets.at(i).c,tweets.at(i).alpha);
                glTranslatef(tweets.at(i).position.x, tweets.at(i).position.y, tweets.at(i).position.z);
                glRotatef(ofGetElapsedTimef()*tweets.at(i).rotateSpeed, 0, 1, 0);
                font.drawString(tweets.at(i).tweetInfo,0,0);
            }else{
                ofSetColor(tweets.at(i).c,tweets.at(i).alpha);
                font.drawString(tweets.at(i).tweetInfo, tweets.at(i).position.x, tweets.at(i).position.y);
            }
            glPopMatrix();
        }
        light.disable();
        glDisable(GL_LIGHTING);
    }glPopMatrix();
    ofPopStyle();
}

void TwitterRain::update(){

    for(int i = 0; i < DISPLAY_TWEET_NUM; i++){
        if(!tweets.at(i).visible) continue;
        tweets.at(i).position.y += tweets.at(i).downSpeed;
        if(tweets.at(i).position.y < ofGetHeight()) continue;
        tweets.at(i).visible = false;
        tweetNum--;
    }
    spentFrames++;
    if(!(spentFrames % 7 == 0)) return;
    if(!(tweetNum < DISPLAY_TWEET_NUM)) return;
    if(putDammyText) putDammyData();
    if(!(JsonReceiver::getInstance().updateNum > 0)) return;
    int index = 0;
    for(int i = 0; i < DISPLAY_TWEET_NUM; i++){
        if(!tweets.at(i).visible){
            index = i;
            break;
        }
    }
    tweets.at(index).tweetInfo = JsonReceiver::getInstance().getRandomTweetInfo().text;
    tweets.at(index).position = ofVec3f(ofRandom(-200,1024),-100,ofRandom(-200, 200));
    tweets.at(index).visible = true;
    tweetNum++;
}

void TwitterRain::putDammyData(){
    putDammyText = false;
    int index = 0;
    for(int i = 0; i < DISPLAY_TWEET_NUM; i++){
        if(!tweets.at(i).visible){
            index = i;
            break;
        }
    }
    tweets.at(index).tweetInfo = JsonReceiver::getInstance().getDammyTextData().at(ofRandom(4));
    tweets.at(index).position = ofVec3f(ofRandom(-200,1024),-100,ofRandom(-200, 200));
    tweets.at(index).visible = true;
    tweetNum++;
}

void TwitterRain::onMouseDown(int x, int y){
    mouseX = x;
    mouseY = y;
}

void TwitterRain::reset(){
    tweetNum = 0;
    tweets = *new vector<Tweet>(DISPLAY_TWEET_NUM);
    for(int index = 0; index < DISPLAY_TWEET_NUM; index++){
        tweets.at(index).visible = false;
    }
}

void TwitterRain::keyPressed(int key){
    switch (key) {
        case 'r':
            bRotation = !bRotation;
            break;
        case 'R':
            reset();
            break;
        case 'P':
            putDammyText = true;
            break;
        default:
            break;
    }
}
