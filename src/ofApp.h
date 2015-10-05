#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxPostGlitch.h"
#include "ofxSyphon.h"

#include "UserAgent.h"
#include "MatrixGenerator.h"

#define COLOR_MAX 255

#include "UserAgentManager.h"

#include "Loading.h"
#include "mode.h"
#include "ofxSuperLog.h"

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
    

    //Syphonで飛ばすため
    ofxSyphonServer mainOutputSyphonServer;
    ofxSyphonServer individualTextureSyphonServer;
    ofxSyphonClient mClient;
    
    //Loading load = *new Loading(2.0,"Loading Tweets...");
    //Mode mode;
};
