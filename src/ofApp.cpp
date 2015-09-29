#include "ofApp.h"


/*ofVec2f ofApp::allocate_matrix(){
    int size = matrix_generator.get_position_num();
    int index = ofRandom(size);;
    while(matrix_generator.get_is_used().at(index)){
        index = ofRandom(size);
    }
    matrix_generator.set_is_used_true(index);
    ofVec2f position = *matrix_generator.get_position().at(index);
    return position;
}*/

/*void ofApp::setup_user_agent(){
    for(int j=0;j<30;j++){
        manager->addAgent(allocate_matrix());
    }
}*/


//--------------------------------------------------------------
void ofApp::setup(){
    //matrix_generator.generate_position(8*2-4, 12);
    
    ofSetFrameRate(60);
    ofBackground(0);
    
    mainOutputSyphonServer.setName("Screen Outputh");//SyphonServer使う上でのセットアップ
    mClient.setup();
    mClient.setApplicationName("Simple Serverh");
    mClient.setServerName("");
    
   // manager = new UserAgentManager();
    //setup_user_agent();
    
    //mode = Load;
    
    ofSetLoggerChannel(ofxSuperLog::getLogger(false, true, ""));
}

//--------------------------------------------------------------
void ofApp::update(){
    //manager->update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
  /*  switch(mode){
        case Load:
            load.draw();
            
            break;
        case Main:
           // manager->draw();
            break;
    }*/

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
      //  manager->addConnection(ofRandom(manager->getUserAgentSize()),
      //                         ofRandom(manager->getUserAgentSize()), ofRandom(50));
    }else if(key == 'n'){
      //  mode = Main;
        ofxSuperLog::getLogger()->setScreenLoggingEnabled(false);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //ofLog((ofLogLevel)400, "mousedragged:" + (string)x + "," + (string)y);
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
   // if(button == 0 && mode == Main){
      //  manager->addAgent(ofVec2f(x, y));
    //}
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

//void ofApp::draw_grid(){
//    ofSetColor(100);
//    ofSetLineWidth(0.1);
//    
//    for(int i =0; i<12;i++){
//        ofLine(0, i*GRID_HEIGHT, ofGetWidth(), i*GRID_HEIGHT);
//    }
//    
//    for(int i =0; i<8*2-4;i++){
//        ofLine(i*GRID_WIDTH,0, i*GRID_WIDTH, ofGetHeight());
//    }
//}


//void ofApp::draw_time_line(){
//    ofFill();
//    float left_x = (8*2-4)*GRID_WIDTH;
//    float width = 4*GRID_WIDTH;
//    ofSetColor(0, 0, 50);
//    ofRect(left_x, 0, width, ofGetHeight());
//}
