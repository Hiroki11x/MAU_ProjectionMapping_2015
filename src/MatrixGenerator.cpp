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
            float dy = ofRandom(-POS_DANDAM_OFFSET,POS_DANDAM_OFFSET)+POSITION_OFFSET;
            position.push_back(new ofVec2f(ix*GRID_WIDTH+dx, iy*GRID_HEIGHT+dy));
            is_used.push_back(false);
        }
    }
}

vector<ofVec2f *> MatrixGenerator::get_position(){
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