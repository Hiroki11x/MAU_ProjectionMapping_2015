/*
 //  UserAgents.cpp
 //  MauInteractive
 //
 //  Created by 櫻木善将 on 2015/09/30.
 //
 //  UserAgentの集合を
 //  UserAgent Model UserAgentのモデル
 //MatrixGenerator 座標生成
 //  Connection UserAgent同士のつながりを描画する
 */

#include "UserAgents.h"

void UserAgents::init(){
    setup_user_agent();
    back_animation.set_fade_duration(2000);
    
    strechyRectSwiper.init();
    strechyRectSwiper.set_color(ofColor::fromHsb(100, 200, 200));
    strechyRectSwiper.set_mode(SwipeMode::SemiCircle);
    
    alphaSwiper.init();
}

void UserAgents::update(){
    for(int i = 0; i < userAgentArray.size(); i++){
        userAgentArray.at(i)->update();//回転アニメーションとか
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
}

void UserAgents::onMouseDown(int x, int y){
    userAgentsSize = userAgentArray.size();
    addConnection(ofRandom(userAgentsSize), ofRandom(userAgentsSize), ofRandom(200));
    strechyRectSwiper.init();
}

void UserAgents::keyPressed(int key){
    userAgentsSize = userAgentArray.size();
    addConnection(ofRandom(userAgentsSize), ofRandom(userAgentsSize), ofRandom(200));
    
    if(key==OF_KEY_UP){
        strechyRectSwiper.set_mode(SwipeMode::Up);
    }else if(key==OF_KEY_DOWN){
        strechyRectSwiper.set_mode(SwipeMode::Down);
    }else if(key==OF_KEY_RETURN){
        strechyRectSwiper.set_mode(SwipeMode::SemiCircle);
    }else if(key==OF_KEY_RIGHT){
        strechyRectSwiper.set_mode(SwipeMode::Right);
    }else if(key==OF_KEY_LEFT){
        strechyRectSwiper.set_mode(SwipeMode::Left);
    }
    strechyRectSwiper.init();
}

void UserAgents::end(){}

void UserAgents::addAgent(ofVec2f position){
    userAgentArray.push_back(new UserAgent());
    userAgentArray.back()->set_position(position);
    userAgentArray.back()->set_color(ofColor::fromHsb(ofRandom(COLOR_MAX/4,COLOR_MAX/3), ofRandom(COLOR_MAX/4,COLOR_MAX), ofRandom(COLOR_MAX/4,COLOR_MAX)));
    userAgentArray.back()->init();
    userAgentArray.back()->set_size(USER_CIRCLE_SIZE);
}

void UserAgents::addConnection(int startIndex,int endIndex,float duration){
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
    
    matrix_generator.generate_position(GENE_X_NUM, GENE_Y_NUM);//6*12個の座標を生成
    int size = matrix_generator.get_position_num();//生成した座標の数
    
    for(int j=0;j<size/3;j++){//GENE_Y_NUM*GENE_X_NUM;
        int index = ofRandom(size);//その座標でどこを使うか選ぶ
        while(matrix_generator.get_is_used().at(index)){//使われていたら選び直し
            index = ofRandom(size);
        }
        matrix_generator.set_is_used_true(index);//使うところは使う(true)に変更
        ofVec2f position = *matrix_generator.get_position().at(index);//そのindexのpositionを取得
        addAgent(position);
    }
}