//
//  TargetMarkerDrawer.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/14.
//
//

#include "TargetMarkerDrawer.h"

void TargetMarkerDrawer::init(float radius){
    for(int i = 0; i < 3; i++){
        insideDrawer.addVertex(ofVec3f( radius * cos(i * 120), radius * sin(i * 120), 0));
        for(float deg = 0; deg < 60; deg += 0.5){
            insideDrawer.addVertex(ofVec3f(radius * cos(float(i * 120) + deg),
                                     radius * sin(float(i * 120) + deg), 0));
            insideDrawer.addVertex(ofVec3f(radius * cos(float(i * 120) + deg),
                                     radius * sin(float(i * 120) + deg), 0));
        }
        insideDrawer.addVertex(ofVec3f( radius * cos(i * 120 + 60), radius * sin(i * 120 + 60), 0));
    }
    for(int i = 0; i < 3; i++){
        outsideDrawer.addVertex(ofVec3f( radius * 1.2 * cos(i * 120), radius * 1.2 * sin(i * 120), 0));
        for(float deg = 0; deg < 90; deg += 0.5){
            outsideDrawer.addVertex(ofVec3f(radius * 1.2 * cos(float(i * 120) + deg),
                                     radius * 1.2 * sin(float(i * 120) + deg), 0));
            outsideDrawer.addVertex(ofVec3f(radius * 1.2 * cos(float(i * 120) + deg),
                                     radius * 1.2 * sin(float(i * 120) + deg), 0));
        }
        outsideDrawer.addVertex(ofVec3f( radius * 1.2 * cos(i * 120 + 90), radius * 1.2 * sin(i * 120 + 90), 0));
    }
}

void TargetMarkerDrawer::drawTargetMarker(){
    
}