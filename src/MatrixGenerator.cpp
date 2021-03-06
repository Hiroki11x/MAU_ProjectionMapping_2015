//
//  MatrixGenerator.cpp
//  MauInteractive
//
//  Created by HirokiNaganuma on 2015/09/13.
//
//

#include "MatrixGenerator.h"

void MatrixGenerator::generate_position(int x_num, int y_num){
    for(int ix =0; ix<x_num ; ix++){
        for(int iy =0; iy<y_num ; iy++){
            float dx = ofRandom(-POS_DANDAM_OFFSET,POS_DANDAM_OFFSET)+POSITION_OFFSET;
            float dy = ofRandom(-POS_DANDAM_OFFSET,POS_DANDAM_OFFSET)+POSITION_OFFSET/2;
            position.push_back(new ofVec3f(ix*GRID_WIDTH+dx, iy*GRID_HEIGHT+dy,ofRandom(300)));
            is_used.push_back(false);
        }
    }
}

vector<ofVec3f *> MatrixGenerator::get_position(){
    return position;
}
vector<bool> MatrixGenerator::get_is_used(){
    return is_used;
}

int MatrixGenerator::get_position_num(){
    return position.size();
}

void MatrixGenerator::set_is_used_true(int index){
    is_used[index] = true;
}

void MatrixGenerator::set_is_used_false(int index){
    is_used[index] = false;
}

void MatrixGenerator::init(){
    for(int i =0;i<is_used.size();i++){
        is_used.at(i)= false;
    }
}