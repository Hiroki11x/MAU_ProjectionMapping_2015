//
//  SpiralDrawer.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/08.
//
//
#include "SpiralDrawer.h"

void SpiralDrawer::init(float scale){
    scale = 1.5;
    model.loadModel("Spiral/s5.stl");
    model.setScale(scale, scale, scale);
}

void SpiralDrawer::drawSpiral(float t){
    model.spentFrame = t * 100;
    model.draw(ofPolyRenderMode::OF_MESH_WIREFRAME);
}