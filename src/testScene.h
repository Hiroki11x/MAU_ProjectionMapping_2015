//
//  testScene.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//

#ifndef testScene_h
#define testScene_h
#include "ofMain.h"
#include "SceneManager.h"
#include "mode.h"
#include "IntroductionManager.h"
#include "SpyMeshSceneManager.h"
#include "UserAgentsSceneManager.h"
#include "AgentAnalyzeSceneManager.h"

#include "ofxSyphon.h"

#include "SceneElement.h"

class testScene : public ofBaseApp{
    
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
    
    SceneManager * manager;
    SceneMode::Mode mode;
    
    int ElementIndex;
    
    ofxSyphonServer mainOutputSyphonServer;
    ofxSyphonServer individualTextureSyphonServer;
    ofxSyphonClient mClient;
};


#endif /* testScene_hpp */
