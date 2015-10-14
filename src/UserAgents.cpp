/*
 //  UserAgents.cpp
 //  MauInteractive
 //
 //  Created by 櫻木善将 on 2015/09/30.
 //
 //  UserAgentの集合を
 //  UserAgent Model UserAgentのモデル
 //  MatrixGenerator 座標生成
 //  Connection UserAgent同士のつながりを描画する
 */

#include "UserAgents.h"

void UserAgents::init(){
    superLogUtil.init();//Logのセットアップ
    matrix_generator.generate_position(GENE_X_NUM, GENE_Y_NUM);//6*12個の座標を生成
    json_num = 0;
    superLogUtil.set_log("init", ofToString(JsonReceiver::getInstance().getUsersInfo().size()));
    
    back_animation.set_fade_duration(2000);
    
    strechyRectSwiper.init();
    strechyRectSwiper.set_color(ofColor::fromHsb(100, 200, 200));
    strechyRectSwiper.set_mode(SwipeMode::SemiCircle);
    
    alphaSwiper.init();
    
    setup_user_agent();//UserAgentをセット
    
    graphLog.setup();
    graphLog.set_height_limit(ofGetWidth()/4);
    
}

void UserAgents::update(){
    
    JsonReceiver::getInstance().recieve();
    
    check_is_json_new();
    
    for(int i = 0; i < userAgentArray.size(); i++){
        userAgentArray.at(i)->update();//回転アニメーションとか
    }
    
    graphLog.update(ofSignedNoise(userAgentsSize,ofRandom(100),ofGetElapsedTimef()));
   
}

void UserAgents::check_agent_size(int delete_adder){//多すぎてたらvectorから消していく
    if(GENE_X_NUM*GENE_Y_NUM < userAgentArray.size()+1){
        int delete_num = userAgentArray.size()+1 - GENE_X_NUM*GENE_Y_NUM +delete_adder;
        for(int i =0 ;i < delete_num ; i++){
            userAgentArray.erase(userAgentArray.begin());
            matrix_generator.set_is_used_false(userAgentArray.at(0)->get_generater_index());
        }
    }
}

void UserAgents::draw(){
    alphaSwiper.draw();
    strechyRectSwiper.draw();//swiperを描画
    back_animation.fade_cross_background(0, 0, 100);//十字の背景
    
    for(int i = 0; i < connections.size(); i++){
        connections.at(i)->drawConnection();
    }
    for(int i = 0; i < userAgentArray.size(); i++){
        userAgentArray.at(i)->draw();
    }
    
    for(int i=0; i<explodeanimations.size();i++){
        explodeanimations.at(i).draw();
    }
    
    graphLog.draw();
}

void UserAgents::onMouseDown(int x, int y){
//    userAgentsSize = userAgentArray.size();
//    addConnection(ofRandom(userAgentsSize), ofRandom(userAgentsSize), ofRandom(200));
//    strechyRectSwiper.init();
}

void UserAgents::keyPressed(int key){
    graphLog.keyPressed(key);
    
    userAgentsSize = userAgentArray.size();
    addConnection(ofRandom(userAgentsSize), ofRandom(userAgentsSize), ofRandom(200));
    
    string tag = "Default";
    if(key==OF_KEY_UP){
        strechyRectSwiper.set_mode(SwipeMode::Up);
        tag = "SwipeMode::Up";
    }else if(key==OF_KEY_DOWN){
        strechyRectSwiper.set_mode(SwipeMode::Down);
        tag = "SwipeMode::Down";
    }else if(key==OF_KEY_RETURN){
        strechyRectSwiper.set_mode(SwipeMode::SemiCircle);
        tag = "SwipeMode::SemiCircle";
    }else if(key==OF_KEY_RIGHT){
        strechyRectSwiper.set_mode(SwipeMode::Right);
        tag = "SwipeMode::Right";
    }else if(key==OF_KEY_LEFT){
        strechyRectSwiper.set_mode(SwipeMode::Left);
        tag = "SwipeMode::Left";
    }
    strechyRectSwiper.init();
    superLogUtil.set_log(tag, ofToString(ofGetElapsedTimef()));//Log出し
    
    check_agent_size(10);
}

void UserAgents::end(){}

void UserAgents::check_is_json_new(){
    int add_num;
    if(json_num<JsonReceiver::getInstance().getUsersInfo().size()){
        add_num = JsonReceiver::getInstance().getUsersInfo().size() - json_num;
        check_agent_size(add_num);
        addAgent(add_num);
        superLogUtil.set_log("check_is_json_new", ofToString(add_num));
    }
}


//TODO positionが足りなくなったらの対応してない
ofVec3f UserAgents::select_position(){
    
    ofVec3f position;
    
    int size = matrix_generator.get_position_num();//生成した座標の数
    int index = ofRandom(size-1);//その座標でどこを使うか選ぶ
    if(size>0){
        while(matrix_generator.get_is_used().at(index)){//使われていたら選び直し
            check_agent_size(1);
            index = ofRandom(size-1);
        }
    }
    
    matrix_generator.set_is_used_true(index);//使うところは使う(true)に変更
    position = *matrix_generator.get_position().at(index);//そのindexのpositionを取得
    position.z = index;
    return position;
    
    //この時のIndexも渡したい
}

void UserAgents::addAgent(int add_num){
    ofVec3f pos3f;
    ofVec2f pos2f;
    for(int i=0;i<add_num;i++){
        
        ////---------Legacy-----------
        userAgentArray.push_back(new UserAgent());
        
        pos3f = select_position();
        userAgentArray.back()->set_generater_index(pos3f.z);
        pos2f.x = pos3f.x;
        pos2f.y = pos3f.y;
        userAgentArray.back()->set_position(pos2f);
        userAgentArray.back()->set_color(ofColor::fromHsb(ofRandom(COLOR_MAX/4,COLOR_MAX/3), ofRandom(COLOR_MAX/4,COLOR_MAX), ofRandom(COLOR_MAX/4,COLOR_MAX)));
        userAgentArray.back()->init();
        userAgentArray.back()->set_size(USER_CIRCLE_SIZE);
        userAgentArray.back()->get_info_from_twitter(
                                                     JsonReceiver::getInstance().getUsersInfo().at(json_num).userName,
                                                     JsonReceiver::getInstance().getUsersInfo().at(json_num).twitterId,
                                                     JsonReceiver::getInstance().getUsersInfo().at(json_num).text,
                                                     JsonReceiver::getInstance().getUsersInfo().at(json_num).friends_count,
                                                     JsonReceiver::getInstance().getUsersInfo().at(json_num).statuses_count,
                                                     JsonReceiver::getInstance().getUsersInfo().at(json_num).followers_count,
                                                     JsonReceiver::getInstance().getUsersInfo().at(json_num).iconURL
                                                     );
        createExplodeAnimation(pos2f);
        json_num++;//json_numはここで
        superLogUtil.set_log("addAgent", ofToString(json_num));
    }
}

void UserAgents::createExplodeAnimation(ofVec2f pos){
    //こういう呼び出しをしてあげれば良い
    explodeanimations.clear();
    explodeanimations.push_back(ExplodeAnimation());
    explodeanimations.back().set_position(pos);
    explodeanimations.back().init();
}

void UserAgents::addConnection(int startIndex,int endIndex,float duration){//Connection追加の際はここを呼ぶ
    userAgentsSize = userAgentArray.size();
    if(startIndex >= userAgentsSize || endIndex >= userAgentsSize || startIndex == endIndex){
        return;
    }
    
    connections.push_back(new Connection(userAgentArray.at(startIndex)->position,
                                         userAgentArray.at(endIndex)->position,
                                         ofColor::fromHsb(100, COLOR_MAX, ofRandom(150,COLOR_MAX)),
                                         duration
                                         ));
}

int UserAgents::getUserAgentSize(){
    return userAgentArray.size();
}
int UserAgents::getConnectionSize(){
    return 0;
}

void UserAgents::setup_user_agent(){//座標をセット
    userAgentArray.clear();
    
    for(int j=0;j<JsonReceiver::getInstance().getUsersInfo().size();j++){//GENE_Y_NUM*GENE_X_NUM;
        addAgent(1);
    }
    //ここは最初のところ
    superLogUtil.set_log("setup_user_agent", ofToString(JsonReceiver::getInstance().getUsersInfo().size()));
}