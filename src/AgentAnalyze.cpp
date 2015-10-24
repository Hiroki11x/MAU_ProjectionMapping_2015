
//
//  AgentAnalyze.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/09.
//
//


#include "AgentAnalyze.h"


void AgentAnalyze::reset(){
    SingleUserManager::user_agent.clear();
}

void AgentAnalyze::init(){
    SingleUserManager::json_num=0;
    check_is_json_new();
    for(int i = 0; i<SingleUserManager::user_agent.size();i++){
        SingleUserManager::user_agent.at(i)->init();
    }
    max_row = ofGetHeight()/90 -1;
    max_column = ofGetWidth()/200-2;
    MAX_AGENT = (max_row)*(max_column+2);
    
    graphlog.setup();
    graphlog.set_height_limit(ofGetWidth()/4);
    
    linebelt.setup_belt(10);
}

void AgentAnalyze::draw(){
    if(mode==0){
        draw_2D();
    }else if(mode ==1){
        draw_3D();
    }else if(mode ==2){
        draw_belt();
    }
    ofDrawBitmapString("Agents Max Size: "+ofToString(MAX_AGENT), 30,40);
    ofDrawBitmapString("Agents Size: "+ofToString(SingleUserManager::json_num), 30,50);
}

void AgentAnalyze::draw_belt(){
    int agent_size = SingleUserManager::user_agent.size();
    ofSetColor(255);
    if(MAX_AGENT < agent_size ){
        SingleUserManager::user_agent.erase(SingleUserManager::user_agent.begin());
        ofxSuperLogUtil::set_log("delete agent","delete");
    }
    linebelt.update_belt();
    linebelt.draw_belt();
    graphlog.draw();
}

void AgentAnalyze::draw_3D(){
    
    int agent_size = SingleUserManager::user_agent.size();
    ofSetColor(255);
    if(MAX_AGENT < agent_size ){
        SingleUserManager::user_agent.erase(SingleUserManager::user_agent.begin());
        ofxSuperLogUtil::set_log("delete agent","delete");
    }

    float x;
    float y;
    
    cam.begin();
    for(int i = 0; i< agent_size ;i++){
        if(i == agent_size-1){
            //            user_agent.at(i).draw_circle();
        }else{
            x = (i/max_row)*200 ;
            y = 90 * (i%max_row -1);
            SingleUserManager::user_agent.at(i)->draw_line(x+30,y+100,100*ofSignedNoise(ofGetElapsedTimef()/100,i));
        }
        cam.setPosition(x+60,y+100, 300*(1+ofSignedNoise(ofGetElapsedTimef()/10)));
        cam.lookAt(ofVec3f(x+60,y+200,0));
    }
    cam.end();
}

void AgentAnalyze::draw_2D(){
    int agent_size = SingleUserManager::user_agent.size();
    ofSetColor(255);
    if(MAX_AGENT < agent_size ){
        SingleUserManager::user_agent.erase(SingleUserManager::user_agent.begin());
    }
    
    float x;
    float y;
    for(int i = 0; i< agent_size ;i++){
        if(i == agent_size-1){
            //            user_agent.at(i).draw_circle();
        }else{
            x = (i/max_row)*200 ;
            y = 90 * (i%max_row -1);
            SingleUserManager::user_agent.at(i)->draw_line(x+30,y+200);
        }
    }
    graphlog.draw();
}


void AgentAnalyze::update(){
    check_is_json_new();
}

void AgentAnalyze::onMouseDown(int x, int y){
}

void AgentAnalyze::keyPressed(int key){//Enterで2D,3Dを切り替え
    graphlog.keyPressed(key);
    if(key==OF_KEY_RETURN){
        mode = (mode+1)%3;
    }else if(key == OF_KEY_TAB){
        reset();
        linebelt.reset_belt();
    }else if(key==OF_KEY_RIGHT_COMMAND){
        linebelt.set_mode();
    }
}

void AgentAnalyze::end(){}

void AgentAnalyze::check_is_json_new(){
    int add_num;
    if(SingleUserManager::json_num<JsonReceiver::getInstance().getUsersInfo().size()){
        add_num = JsonReceiver::getInstance().getUsersInfo().size() - SingleUserManager::json_num;
        addAgent(add_num);
        ofxSuperLogUtil::set_log("add agent","add "+ofToString(add_num)+" agents");
        linebelt.add_line_num(add_num*5);
    }
}

void AgentAnalyze::addAgent(int add_num){
    ofVec2f pos;
    for(int i=0;i<add_num;i++){
        SingleUserManager::user_agent.push_back(new SingleAgent());
        SingleUserManager::user_agent.back()->init();
        SingleUserManager::user_agent.back()->get_info_from_twitter(
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).userName,
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).twitterId,
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).text,
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).friends_count,
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).statuses_count,
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).followers_count,
                                                JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).iconURL);
        ofxSuperLogUtil::set_log("Agent added",ofToString(JsonReceiver::getInstance().getUsersInfo().at(SingleUserManager::json_num).twitterId)+" join");
        SingleUserManager::json_num++;//json_numはここで
        graphlog.update(ofSignedNoise(SingleUserManager::json_num,ofRandom(100),ofGetElapsedTimef()));
    }
}
