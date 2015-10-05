//
//  3DModelDrawer.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/01.
//
//
#include "ModelDrawer.h"

void ModelDrawer::drawPercentage(){
    ofNoFill();
    ofRect(50, 50, 300, 50);
    ofFill();
    ofRect(50, 50, 300 * (float(addedIndicesSize) / float(indicesSize)), 50);
}

void ModelDrawer::setPrimitiveMode(ofPrimitiveMode primitiveMode){
    this->primitiveMode = primitiveMode;
}
