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
    font.setup(60, 0.3);
    font.loadFont("Arial.ttf", 20);
    font.loadFont("Yumin Demibold",128,true,true,0.3f,0,true)||font.loadSubFont("YuMincho");
    font.loadSubFont(OF_TTF_SERIF,1.2,-0.02);
    font.loadSubFont("Geeza Pro",1,-0.04,0x0600,0x06FF,"arab");
    font.useProportional(true);
    font.useVrt2Layout(true);
    font.setLineHeight(font.getFontSize()*1.5);
    align = UL2_TEXT_ALIGN_V_TOP|UL2_TEXT_ALIGN_CENTER;
    strAlign="top-center [8]";
    strDirection="Left to Right (TTB)";
   // glEnable(GL_CULL_FACE);//カリングON
    glCullFace(GL_BACK);//裏面をカリング
    glEnable(GL_DEPTH_TEST);
    renderingMode=false;
    bRotation=false;
    
    //font2.setup(60, 0.3);
    font2.loadFont("Arial.ttf", 10);
    font2.loadFont("Yumin Demibold",32,true,true,0.3f,0,true)||font2.loadSubFont("YuMincho");
    font2.loadSubFont(OF_TTF_SERIF,1.2,-0.02);
    font2.loadSubFont("Geeza Pro",1,-0.04,0x0600,0x06FF,"arab");
    font2.useProportional(true);
    font2.useVrt2Layout(true);
    font2.setLineHeight(font.getFontSize()*1.5);
}

void TwitterRain::draw(){
    ofSetColor(255);
    int w,h,x,y;
    x=100;
    y=100;
    w=mouseX-x;
    h=mouseY-y;
    
    ofSetColor(255,50,50,255);
    ofLine(0,y,ofGetWidth(),y);
    ofLine(x,0,x,ofGetHeight());
    
    ofSetColor(255,50,50,255);
    ofLine(mouseX,0,mouseX,ofGetHeight());
    ofLine(0,mouseY,ofGetWidth(),mouseY);
    
    glPushMatrix();{
        if(renderingMode){
            light.enable();
            light.setPosition(ofGetWidth()*.5,ofGetHeight()*.5,ofGetWidth());
        }
        for(int i = 0; i < tweets.size(); i++){
            glPushMatrix();
            if(bRotation){
                ofSetColor(25,255,25,tweets.at(i).alpha);
                //3D
              /*  ofRectangle rc= font.getStringBoundingBox(tweets.at(i).tweetInfo,x,y,w,h,align);
                glTranslatef(ofGetWidth()*.5,0,0);
                glRotatef(ofGetElapsedTimef()*tweets.at(i).rotateSpeed,0,1,0);
                glTranslatef(x-rc.x -rc.width*.5,0,0);
                */
                //2D
                ofRectangle rc= font2.getStringBoundingBox(tweets.at(i).tweetInfo,x,y,w,h,align);
                glTranslatef(tweets.at(i).position.x, tweets.at(i).position.y, tweets.at(i).position.z);
                glRotatef(ofGetElapsedTimef()*tweets.at(i).rotateSpeed, 0, 1, 0);
                glTranslatef(x-rc.x -rc.width*.5,0,0);
                font2.drawString(tweets.at(i).tweetInfo,0,0);
                
            }else{
           // if(renderingMode){
                ofSetColor(25,255,25,tweets.at(i).alpha);
                //3D
                /*font.draw3dString(tweets.at(i).tweetInfo,
                                  tweets.at(i).position.x,
                                  tweets.at(i).position.y,
                                  tweets.at(i).position.z,
                                  300,300,align);*/
                //2D
                font2.drawString(tweets.at(i).tweetInfo, tweets.at(i).position.x, tweets.at(i).position.y);
          /*  }else{
                ofSetColor(127,255,127,255);
                glPolygonMode(GL_FRONT, GL_LINE);
                font.draw3dString("this is a 3dfont test",x,y,0,w,h,align);
                glPolygonMode(GL_FRONT, GL_FILL);
            }*/
            }
            glPopMatrix();
        }
        light.disable();
        glDisable(GL_LIGHTING);
        
    }glPopMatrix();
}

void TwitterRain::update(){
    
    if(spentFrames % 7 == 0){
        if(tweets.size() < DISPLAY_TWEET_NUM){
            if(JsonReceiver::getUsersInfo().size() > 0){
                wstring twi;
                twi.append(JsonReceiver::getRandomTweetInfo().text);
                tweets.push_back((Tweet){twi,ofVec3f(ofRandom(-200,1024),-100,ofRandom(-200, 200)),ofRandom(-30,30),ofRandom(8,15),ofRandom(100,255)});
                tweetDebug = false;
            }
        }
    }
    for(int i = 0; i < tweets.size(); i++){
        
        tweets.at(i).position.y += tweets.at(i).downSpeed;
        if(tweets.at(i).position.y > ofGetHeight()){
            tweets.erase(tweets.begin() + i);
            i--;
        }
    }
    spentFrames++;
}

void TwitterRain::onMouseDown(int x, int y){
    mouseX = x;
    mouseY = y;
}

void TwitterRain::keyPressed(int key){

    z = key;
    if(key == 'p'){
        tweetDebug = true;
    }else if(key == 'r'){
        bRotation = !bRotation;
    }else if (key == 'l'){
        renderingMode = !renderingMode;
    }
}
