//
//  testScene.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//

#include "testScene.h"

void testScene::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    ofDisableArbTex();
    
    manager = new SpyMeshSceneManager();
    manager->setup();
    mode = SceneMode::Introduction;
    
}

//--------------------------------------------------------------
void testScene::update(){
    manager->update();
}

//--------------------------------------------------------------
void testScene::draw(){
    manager->draw();
}

//--------------------------------------------------------------
void testScene::keyPressed(int key){
    if(key == 'f'){
        ofToggleFullscreen();
    }else if (key == ' '){
        if(!manager->nextElement()){
            delete manager;
            //switchで次のmanagerのインスタンス作成
            switch (mode) {
                case SceneMode::Introduction:
                    manager = new SpyMeshSceneManager();
                    mode = SceneMode::SpyMesh;
                    break;
                case SceneMode::SpyMesh:
                    manager = new IntroductionManager();
                    mode = SceneMode::Introduction;
                    break;
                default:
                    break;
            }
            
            manager->setup();
        }
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
