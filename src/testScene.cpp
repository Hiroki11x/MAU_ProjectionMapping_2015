//
//  testScene.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//

#include "testScene.h"

void testScene::setup(){
    FontManager::mbigfont.loadFont("03スマートフォントUI.otf",15);
    FontManager::mfont.loadFont("03スマートフォントUI.otf",10);
    FontManager::msmallfont.loadFont("03スマートフォントUI.otf",5);
    
    ofSetVerticalSync(true);
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofDisableArbTex();
    
    mainOutputSyphonServer.setName("Screen Outputh");//SyphonServer使う上でのセットアップ
    mClient.setup();
    mClient.setApplicationName("Simple Serverh");
    mClient.setServerName("");
    
    manager = new UserAgentsSceneManager();
    manager->setup();
    mode=SceneMode::UserAgent;

    JsonReceiver::getInstance().init();
    thread.startThread();
    
    isBackAuto = false;
}

void testScene::exit(){
    thread.stopThread();
}

//--------------------------------------------------------------
void testScene::update(){
    manager->update();
}

//--------------------------------------------------------------
void testScene::draw(){
    manager->draw();
    mClient.draw(50, 50);
    mainOutputSyphonServer.publishScreen();
    ofSetWindowTitle("FPS: "+ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testScene::keyPressed(int key){
    manager->keyPressed(key);
    if(key == 'f'){
        ofToggleFullscreen();
//    }else if (key == ' '){
//        if(!manager->nextElement()){
//            delete manager;
//            //switchで次のmanagerのインスタンス作成
//            switch (mode) {
//                case SceneMode::UserAgent:
//                    manager = new UserAgentsSceneManager();
//                    mode = SceneMode::AgentAnalyze;
//                    break;
//                case SceneMode::AgentAnalyze:
//                    manager = new AgentAnalyzeSceneManager();
//                    mode = SceneMode::Introduction;
//                    break;
//                default:
//                    break;
//            }
//            manager->reset();
//            manager->setup();
//            
//        }
    }else if(key ==' '){
        isBackAuto = !isBackAuto;
        ofSetBackgroundAuto(isBackAuto);
    }
}

//--------------------------------------------------------------
void testScene::keyReleased(int key){

}

//--------------------------------------------------------------
void testScene::mouseMoved(int x, int y ){
  
    //ofLogNotice() << "mouseDragged:" << x << "," << y << endl;
    
}

//--------------------------------------------------------------
void testScene::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testScene::mousePressed(int x, int y, int button){
    manager->onMouseDown(x, y);
}

//--------------------------------------------------------------
void testScene::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testScene::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testScene::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testScene::dragEvent(ofDragInfo dragInfo){
    
}
