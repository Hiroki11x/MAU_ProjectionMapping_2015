//
//  GlidShoot.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/19.
//
//

#include "GlidShoot.h"

void GlidShoot::init(){
    glids = *new vector<Glid>(H_GRID * V_GRID);
}

void GlidShoot::draw(){
    ofPushMatrix();
    ofTranslate(SIDE_MARGIN, TOP_MARGIN);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(false);
    ofSetColor(0, 0, 0, 10);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    //ofSetColor(0, 255, 255);
    for(int i = 0; i < H_GRID * V_GRID; i++){
        ofPushMatrix();
        ofTranslate((i % H_GRID) * GRID_SIZE , (i / H_GRID) * GRID_SIZE);
        if(glids.at(i).drawGlid){
            ofSetColor(glids.at(i).c);
            ofRect(5, 5, GRID_SIZE - 10,GRID_SIZE - 10);
        }
        ofPopMatrix();
    }
    ofPopMatrix();
}

void GlidShoot::update(){
    
   /* spentFrames++;
    if(spentFrames % 2){
        keyPressed(keys[(int)ofRandom(14)]);
    }*/
    
    
    for(int i = 0; i < H_GRID * V_GRID; i++){
        if(glids.at(i).drawGlid){
            glids.at(i).restDrawFrames--;
            if(glids.at(i).restDrawFrames == 0){
                glids.at(i).drawGlid = false;
                if(i >= H_GRID){
                    glids.at(i - H_GRID).drawGlid = true;
                    glids.at(i - H_GRID).drawFrames = glids.at(i).drawFrames;
                    glids.at(i - H_GRID).restDrawFrames = glids.at(i).drawFrames;
                    glids.at(i - H_GRID).c = glids.at(i).c;
                }
            }
        }
    }
}

void GlidShoot::onMouseDown(int x, int y){}

void GlidShoot::keyPressed(int key){
    switch (key) {
        case 'q':
            glids.at(H_GRID * (V_GRID - 1)).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1)).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1)).drawFrames = glids.at(H_GRID * (V_GRID - 1)).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1)).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 'w':
            glids.at(H_GRID * (V_GRID - 1) + 1).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 1).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 1).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 1).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 1).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 'e':
            glids.at(H_GRID * (V_GRID - 1) + 2).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 2).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 2).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 2).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 2).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 'r':
            glids.at(H_GRID * (V_GRID - 1) + 3).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 3).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 3).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 3).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 3).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 't':
            glids.at(H_GRID * (V_GRID - 1) + 4).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 4).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 4).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 4).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 4).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 'y':
            glids.at(H_GRID * (V_GRID - 1) + 5).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 5).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 5).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 5).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 5).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 'u':
            glids.at(H_GRID * (V_GRID - 1) + 6).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 6).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 6).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 6).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 6).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 'i':
            glids.at(H_GRID * (V_GRID - 1) + 7).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 7).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 7).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 7).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 7).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 'o':
            glids.at(H_GRID * (V_GRID - 1) + 8).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 8).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 8).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 8).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 8).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 'p':
            glids.at(H_GRID * (V_GRID - 1) + 9).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 9).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 9).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 9).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 9).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case '@':
            glids.at(H_GRID * (V_GRID - 1) + 10).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 10).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 10).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 10).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 10).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case '[':
            glids.at(H_GRID * (V_GRID - 1) + 11).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 11).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 11).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 11).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 11).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 'a':
            glids.at(H_GRID * (V_GRID - 1) + 12).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 12).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 12).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 12).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 12).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 's':
            glids.at(H_GRID * (V_GRID - 1) + 13).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 13).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 13).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 13).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 13).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
       /* case 'd':
            glids.at(H_GRID * (V_GRID - 1) + 14).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 14).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 14).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 14).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 14).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 'f':
            glids.at(H_GRID * (V_GRID - 1) + 15).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 15).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 15).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 15).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 15).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 'g':
            glids.at(H_GRID * (V_GRID - 1) + 16).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 16).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 16).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 16).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 16).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;
        case 'h':
            glids.at(H_GRID * (V_GRID - 1) + 17).drawGlid = true;
            glids.at(H_GRID * (V_GRID - 1) + 17).restDrawFrames = ofRandom(MAX_DRAW_FRAME);
            glids.at(H_GRID * (V_GRID - 1) + 17).drawFrames = glids.at(H_GRID * (V_GRID - 1) + 17).restDrawFrames;
            glids.at(H_GRID * (V_GRID - 1) + 17).c = ofColor::fromHsb(ofRandom(120, 190), 255, 255);
            break;*/
        default:
            break;
    }
}

void GlidShoot::stop(){
    ofSetBackgroundAuto(true);
}