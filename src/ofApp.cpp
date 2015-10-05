#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground(0);
    
    mainOutputSyphonServer.setName("Screen Outputh");//SyphonServer使う上でのセットアップ
    mClient.setup();
    mClient.setApplicationName("Simple Serverh");
    mClient.setServerName("");

    ofSetLoggerChannel(ofxSuperLog::getLogger(false, true, ""));
}

//--------------------------------------------------------------
void ofApp::update(){
    //manager->update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //Drawを最後に書くとそれまでに書いたものをSyphonで送信する
    mClient.draw(50, 50);
    mainOutputSyphonServer.publishScreen();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f'){
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == ' '){
    }else if(key == 'n'){
        ofxSuperLog::getLogger()->setScreenLoggingEnabled(false);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    ofLogNotice() << "mouseDragged:" << x << "," << y << endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

