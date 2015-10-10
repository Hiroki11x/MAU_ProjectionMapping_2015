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
    
    renderingMode=true;
    bRotation=false;
}

void TwitterRain::draw(){
    
    int w,h,x,y;
    x=100;
    y=100;
    w=mouseX-x;
    h=mouseY-y;
    
    //base line
    ofSetColor(255,50,50,255);
    ofLine(0,y,ofGetWidth(),y);
    ofLine(x,0,x,ofGetHeight());
    
    //cursor
    ofSetColor(255,50,50,255);
    ofLine(mouseX,0,mouseX,ofGetHeight());
    ofLine(0,mouseY,ofGetWidth(),mouseY);
    
    //draw
    glPushMatrix();{
        
        if(renderingMode){
            light.enable();
            light.setPosition(ofGetWidth()*.5,ofGetHeight()*.5,ofGetWidth());
        }
        
        for(int i = 0; i < tweets.size(); i++){
            glPushMatrix();
            if(bRotation){
                
                ofRectangle rc= font.getStringBoundingBox(tweets.at(i).tweetInfo,x,y,w,h,align);
                glTranslatef(ofGetWidth()*.5,0,0);
                glRotatef(ofGetElapsedTimef()*tweets.at(i).rotateSpeed,0,1,0);
                glTranslatef(x-rc.x -rc.width*.5,0,0);
                
            }
            
            if(renderingMode){
                ofSetColor(25,255,25,255);
                font.draw3dString(tweets.at(i).tweetInfo,
                                  tweets.at(i).position.x,
                                  tweets.at(i).position.y,
                                  tweets.at(i).position.z,
                                  300,300,align);
            }else{
                ofSetColor(127,255,127,255);
                glPolygonMode(GL_FRONT, GL_LINE);
                font.draw3dString("this is a 3dfont test",x,y,0,w,h,align);
                glPolygonMode(GL_FRONT, GL_FILL);
            }

            glPopMatrix();
        }
        
        light.disable();
        glDisable(GL_LIGHTING);
        
    }glPopMatrix();
}

void TwitterRain::update(){
    
    if(spentFrames % 5 == 0){
        if(tweets.size() < DISPLAY_TWEET_NUM){
            //if(tweetDebug){
            JsonReceiver::recieve();
            if(JsonReceiver::usersInfo.size() > 0){
                JsonReceiver::UserInfo info = JsonReceiver::getRandomTweetInfo();
            
                wstring twi;
                string text = info.text;
            
                twi.append(convToWString(text));
                tweets.push_back((Tweet){twi,ofVec3f(ofRandom(0,1024),-100,ofRandom(-200, 200)),ofRandom(30),ofRandom(10,20)});
                tweetDebug = false;
            }
        }
    }
    for(int i = 0; i < tweets.size(); i++){
        
        tweets.at(i).position.y += tweets.at(i).downSpeed;
        if(tweets.at(i).position.y > ofGetHeight() + 20){
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
    }
}

wstring TwitterRain::convToWString(string src) {
    
#ifdef TARGET_WIN32
    wstring dst = L"";
    typedef codecvt<wchar_t, char, mbstate_t> codecvt_t;
    
    locale loc = locale("");
    if(!std::has_facet<codecvt_t>(loc))
        return dst;
    
    const codecvt_t & conv = use_facet<codecvt_t>(loc);
    
    const std::size_t size = src.length();
    std::vector<wchar_t> dst_vctr(size);
    
    if (dst_vctr.size() == 0)
        return dst;
    
    wchar_t * const buf = &dst_vctr[0];
    
    const char * dummy;
    wchar_t * next;
    mbstate_t state = {0};
    const char * const s = src.c_str();
    
    if (conv.in(state, s, s + size, dummy, buf, buf + size, next) == codecvt_t::ok)
        dst = std::wstring(buf, next - buf);
    
    return dst;
#elif defined __clang__
    wstring dst = L"";
    for (int i=0; i<src.size(); ++i)
        dst += src[i];
#if defined(__clang_major__) && (__clang_major__ >= 4)
    dst = convToUCS4<wchar_t>(dst);
#endif
    return dst;
#else
    return convToUCS4<char>(src);
#endif
}


template <class T>
wstring TwitterRain::convToUCS4(basic_string<T> src) {
    wstring dst = L"";
    // convert UTF-8 on char or wchar_t to UCS-4 on wchar_t
    int size = src.size();
    int index = 0;
    while (index < size) {
        wchar_t c = (unsigned char)src[index];
        if (c < 0x80) {
            dst += (c);
        }else if (c < 0xe0) {
            if (index + 1 < size) {
                dst += (((c & 0x1f) << 6) | (src[index+1] & 0x3f));
                index++;
            }
        }else if (c < 0xf0) {
            if (index + 2 < size) {
                dst += (((c & 0x0f) << 12) | ((src[index+1] & 0x3f) << 6) |
                        (src[index+2] & 0x3f));
                index += 2;
            }
        }else if (c < 0xf8) {
            if (index + 3 < size) {
                dst += (((c & 0x07) << 18) | ((src[index+1] & 0x3f) << 12) |
                        ((src[index+2] & 0x3f) << 6) | (src[index+3] & 0x3f));
                index += 3;
            }
        }else if (c < 0xfc) {
            if (index + 4 < size) {
                dst += (((c & 0x03) << 24) | ((src[index+1] & 0x3f) << 18) |
                        ((src[index+2] & 0x3f) << 12) | ((src[index+3] & 0x3f) << 6) |
                        (src[index+4] & 0x3f));
                index += 4;
            }
        }else if (c < 0xfe) {
            if (index + 5 < size) {
                dst += (((c & 0x01) << 30) | ((src[index+1] & 0x3f) << 24) |
                        ((src[index+2] & 0x3f) << 18) | ((src[index+3] & 0x3f) << 12) |
                        ((src[index+4] & 0x3f) << 6) | (src[index+5] & 0x3f));
                index += 5;
            }
        }
        index++;
    }
    return dst;
}
