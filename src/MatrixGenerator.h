//
//  MatrixGenerator.h
//  MauInteractive
//
//  Created by HirokiNaganuma on 2015/09/13.
//
//

#ifndef __MauInteractive__MatrixGenerator__
#define __MauInteractive__MatrixGenerator__

#include <stdio.h>
#include "ofMain.h"

#define GRID_WIDTH 128
#define GRID_HEIGHT 64

#define POSITION_OFFSET 20
#define POS_DANDAM_OFFSET 15

class MatrixGenerator{
private:
    vector<ofVec2f *>position;
    vector<bool> is_used;
public:
    MatrixGenerator(){};

    void generate_position(int x_num, int y_num);//8*12のポジションを生成
    vector<ofVec2f *> get_position();//p
    vector<bool> get_is_used();
    int get_position_num();
    void set_is_used_true(int index);
};

#endif /* defined(__MauInteractive__MatrixGenerator__) */
