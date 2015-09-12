#include "ofApp.h"


void ofApp::setup_user_agent(){
    for(int j=0;j<3;j++){
        user_agent.push_back(new UserAgent());//動的配列生成
        user_agent.back()->set_position(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
        user_agent.back()->set_color(ofColor::fromHsb(ofRandom(COLOR_MAX), COLOR_MAX, COLOR_MAX));
        user_agent.back()->set_size(40);
        user_agent.back()->init();
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground(0);

    //SyphonServer使う上でのセットアップ
    mainOutputSyphonServer.setName("Screen Outputh");
    mClient.setup();
    mClient.setApplicationName("Simple Serverh");
    mClient.setServerName("");
    
    setup_user_agent();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for(int i=0;i<user_agent.size();i++){
        user_agent.at(i)->draw();
    }
    
    //Drawを最後に書くとそれまでに書いたものをSyphonで送信する
    mClient.draw(50, 50);
    mainOutputSyphonServer.publishScreen();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
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