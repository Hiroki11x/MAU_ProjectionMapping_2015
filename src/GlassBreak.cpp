//
//  GlassBreak.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/21.
//
//
#include "GlassBreak.h"

void GlassBreak::init(){
    glassModel.loadModel("glass.stl");
    glassModel.setScale(1, 1, 1);
    glassTriangleNum = glassModel.getMesh(0).indices.size()/3.0;
    glassMesh.useColors = true;
    reset();
}

void GlassBreak::update(){
    
    switch (mode) {
        case DrawGlass:
            if(addedVertex >= glassTriangleNum * 3) return;
            drawingMesh.addVertex(glassMesh.vertices.at(addedVertex));
            drawingMesh.addColor(glassMesh.colors.at(addedVertex));
            addedVertex++;
            break;
        case DrawedGlass:
            spentFrames++;
            break;
        case Break:
            for(int i = 0; i < glassTriangleNum; i++){
                ofVec3f center = (glassMesh.vertices.at(3 * i) + glassMesh.vertices.at(3 * i + 1) + glassMesh.vertices.at(3 * i + 2)) / 3.0;
                glassMesh.setVertex(3 * i, ofVec3f((glassMesh.vertices.at(3 * i) - center).rotated(crashRotation.at(i).x,crashRotation.at(i).y, crashRotation.at(i).z) + center + crashSpeeds.at(i)));
                glassMesh.setVertex(3 * i + 1, ofVec3f((glassMesh.vertices.at(3 * i + 1) - center).rotated(crashRotation.at(i).x,crashRotation.at(i).y, crashRotation.at(i).z) + center + crashSpeeds.at(i)));
                glassMesh.setVertex(3 * i + 2, ofVec3f((glassMesh.vertices.at(3 * i + 2) - center).rotated(crashRotation.at(i).x,crashRotation.at(i).y, crashRotation.at(i).z) + center + crashSpeeds.at(i)));
            }
            break;
        default:
            break;
    }
}

void GlassBreak::draw(){
    cam.begin();
    ofDisableDepthTest();
    ofDisableAlphaBlending();
    ofDisableBlendMode();
    switch (mode) {
        case DrawGlass:
            ofBackground(255);
            ofSetLineWidth(3);
            drawingMesh.draw(OF_MESH_WIREFRAME);
            break;
        case DrawedGlass:
            ofBackground(255);
            
            drawingMesh.draw(OF_MESH_FILL);
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofSetColor(255, 255, 255, 255 - spentFrames);
            ofRect(-800, -800, 1600,1600);
            ofDisableBlendMode();
            ofDisableAlphaBlending();
            ofSetLineWidth(3);
            drawingMesh.draw(OF_MESH_WIREFRAME);
            break;
        case Break:
            ofBackground(0);
            glassMesh.draw(OF_MESH_FILL);
            break;
        default:
            break;
    }
    cam.end();
}

void GlassBreak::onMouseDown(int x, int y){}
void GlassBreak::reset(){
    glassMesh.clear();
    drawingMesh.clear();
    for(int i = 0; i < glassModel.getMesh(0).indices.size(); i++){
        glassMesh.addVertex(glassModel.getMesh(0).vertices.at(glassModel.getMesh(0).indices.at(i)) * 46);
        glassMesh.addColor(ofColor::fromHsb(ofRandom(255), ofRandom(100,255), 255, ofRandom(100,255)));
    }
    for(int i = 0; i < glassTriangleNum; i++){
        crashSpeeds.push_back(ofVec3f(glassMesh.vertices.at(i * 3).x * 0.1 + ofRandom(-3.0, 3.0),glassMesh.vertices.at(i * 3).y * 0.01 - 15, ofRandom(10)));
        crashRotation.push_back(ofVec3f(ofRandom(-3.0, 3.0),ofRandom(-3.0, 3.0),ofRandom(-3.0, 3.0)));
    }
    mode = DrawGlass;
    drawCounter = 0;
    spentFrames = 0;
    addedVertex = 0;
}

void GlassBreak::keyPressed(int key){
    switch (key) {
        case 'R':
            reset();
            break;
        case 'd':
            mode = DrawedGlass;
            break;
        case 'b':
            mode = Break;
            break;
        default:
            break;
    }
}

void GlassBreak::stop(){
    ofBackground(0);
}