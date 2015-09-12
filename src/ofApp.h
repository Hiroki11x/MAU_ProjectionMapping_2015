#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxPostGlitch.h"
#include "ofxSyphon.h"

#include "UserAgent.h"

#define COLOR_MAX 255

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void setup_user_agent();
    
    vector<UserAgent *> user_agent;

    //Syphonで飛ばすため
    ofxSyphonServer mainOutputSyphonServer;
    ofxSyphonServer individualTextureSyphonServer;
    ofxSyphonClient mClient;

};
