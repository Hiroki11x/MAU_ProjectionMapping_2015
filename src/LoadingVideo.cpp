//
//  LoadingVideo.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/24.
//
//

#include "LoadingVideo.h"

void LoadingVideo::reset(){
    
}

void LoadingVideo::update(){
    if(mode){
        if(video.isPlaying())video.update();
    }else{
        if(video2.isPlaying())video2.update();
    }
    check_is_json_new();
}


void LoadingVideo::check_is_json_new(){
    int add_num;
    if(SingleUserManager::json_num<JsonReceiver::getInstance().getUsersInfo().size()){
        add_num = JsonReceiver::getInstance().getUsersInfo().size() - SingleUserManager::json_num;
        addAgent(add_num);
        ofxSuperLogUtil::set_log("add agent","add "+ofToString(add_num)+" agents");
    }
}

void LoadingVideo::addAgent(int add_num){
    ofVec2f pos;
    for(int i=0;i<add_num;i++){
//        SingleUserManager::user_agent.push_back(new SingleAgent());
//        SingleUserManager::user_agent.back()->init();
//        SingleUserManager::user_agent.back()->get_info_from_twitter(
//                                                                    JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).userName,
//                                                                    JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).twitterId,
//                                                                    JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).text,
//                                                                    JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).friends_count,
//                                                                    JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).statuses_count,
//                                                                    JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).followers_count,
//                                                                    JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).iconURL);
//        ofxSuperLogUtil::set_log("Agent added",ofToString(JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).twitterId)+" join");
        SingleUserManager::json_num++;//json_numはここで
    }
}


void LoadingVideo::draw(){
    ofSetColor(255);
    if(mode){
        if(video.isPlaying())video.draw(ofGetWidth()/2-video.width/2, ofGetHeight()/2-video.height/2,video.width,video.height);
    }else{
        if(video2.isPlaying())video2.draw(ofGetWidth()/2-video2.width/2, ofGetHeight()/2-video2.height/2,video2.width,video2.height);
    }

}

void LoadingVideo::init(){
    video.loadMovie("Loading.mp4");
    video.setLoopState(OF_LOOP_NORMAL);
    video2.loadMovie("plz_tweet.mp4");
    video2.setLoopState(OF_LOOP_NORMAL);
}

void LoadingVideo::end(){
    
}

void LoadingVideo::onMouseDown(int x,int y){
    
}

void LoadingVideo::keyPressed(int key){
    if (key == OF_KEY_RETURN) {
        mode = !mode;
        if(mode){
            video.play();
        }else{
            video2.play();
        }
    }else if(key == OF_KEY_TAB||key=='1'||key=='2'||key=='3'||key=='4'||key=='5'){//Loadingは止めとく
        video.stop();
        video.firstFrame();
        video2.stop();
        video2.firstFrame();
    }
}