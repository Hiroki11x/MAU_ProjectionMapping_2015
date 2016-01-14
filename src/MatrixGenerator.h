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

#define GRID_WIDTH 220
#define GRID_HEIGHT 70

#define POSITION_OFFSET 100
#define POS_DANDAM_OFFSET 15

class MatrixGenerator{
private:
    vector<ofVec3f *>position;
    vector<bool> is_used;
public:
    MatrixGenerator(){};
    
    void init();

    void generate_position(int x_num, int y_num);//8*12のポジションを生成
    vector<ofVec3f *> get_position();//p
    vector<bool> get_is_used();
    int get_position_num();
    void set_is_used_true(int index);
    void set_is_used_false(int index);
};

#endif /* defined(__MauInteractive__MatrixGenerator__) */
