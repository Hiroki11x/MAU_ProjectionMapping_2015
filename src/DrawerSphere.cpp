//
//  DrawerSphere.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/05.
//
//
#include "DrawerSphere.h"

void DrawerSphere::drawSphere(ofVec3f position){
    model.setPosition(position.x,position.y,position.z);
    model.draw(ofPolyRenderMode::OF_MESH_FILL);
}

void DrawerSphere::drawSphere(ofVec3f position, float scale){
    model.setScale(scale, scale, scale);
    drawSphere(position);
}

DrawerSphere::DrawerSphere(float scale){
    model.loadModel("sphere.stl");
    model.setScale(scale, scale, scale);
}