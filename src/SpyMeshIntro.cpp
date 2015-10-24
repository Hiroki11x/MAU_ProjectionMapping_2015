//
//  SpyMeshIntro.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/02.
//
//
#include "SpyMeshIntro.h"

void SpyMeshIntro::update(){
    
    if(spentFrames < 650){
        camera.lookAt(ofPoint(ofGetWidth()/2 + 400, ofGetHeight()/2,70));
        camera.setPosition(ofGetWidth()/2 -ofGetWidth() * 5 * (1.0 - (float)spentFrames * 25.0 / (float)garallyModelDrawer.verticesSize),
                           ofGetHeight() * (1.0 - 0.5 * (float)spentFrames * 25.0 / (float)garallyModelDrawer.verticesSize),
                           70);
    }else{
        cameraRotateFrames++;
        if(cameraRotateFrames < waitFrame){
            if(cameraRotateFrames < rotateFrame){
                cameraPosition += (nextCameraPosition - befCameraPosition) / float(rotateFrame);
                cameraLookPoint += (nextCameraLookPoint - befCameraLookPoint) / float(rotateFrame);
                camera.setPosition(cameraPosition);
                camera.lookAt(cameraLookPoint);
            }
        }else{
            cameraRotateFrames = 0;
            befCameraPosition = cameraPosition;
            nextCameraPosition = ofVec3f(ofGetWidth()/2 + 400 + ofRandom(-500, 500), ofGetHeight()/2 + ofRandom(-500, 500),70 + ofRandom(-500, 500));
            befCameraLookPoint = cameraLookPoint;
            nextCameraLookPoint = ofPoint(ofGetWidth()/2 + ofRandom(-500,500), ofGetHeight()/2 + ofRandom(-150, 150),70 + ofRandom(-500,500));
            waitFrame = ofRandom(50,100);
            rotateFrame = ofRandom(10,50);
        }
    }
        
    for(int i = 0; i < ADD_TRIANGLE_PER_UPDATE; i++){
        targetPoint = garallyModelDrawer.addVertex();
    }
    spentFrames+=1;
    gui.update();
    if(spentFrames % 60 != 0) return;
    updateNetworkLine();
    emitPoint = lineEmitPoints[int(ofRandom(0,4))];
    fpsPoint = ofVec2f(ofRandom(100, ofGetWidth() - 100), ofRandom(70, ofGetHeight() -70));
}

void SpyMeshIntro::updateNetworkLine(){
    networkLine.clear();
    int pointNum = ofRandom(10, 20);
    for(int i = 0; i < pointNum; i++){
        networkLine.addVertex(garallyModelDrawer.vertices[int(ofRandom(garallyModelDrawer.indicesSize))]);
    }
    networkLine.setMode(OF_PRIMITIVE_LINE_LOOP);
}

void SpyMeshIntro::draw(){
    
    ofDisableDepthTest();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    backShader.load("","shader.frag");
    backShader.begin();
    backShader.setUniform1f("u_time", ofGetElapsedTimef());
    backShader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    ofRect(0,0,ofGetWidth(), ofGetHeight());
    backShader.end();

    gui.drawGui();
    if(drawFPSAndSPFMode){
        ofSetColor(fpsColor);
        gui.graph.font->drawString(ofToString(spentFrames) + ":" + ofToString(ofGetFrameRate()), fpsPoint.x, fpsPoint.y);
    }
    light.enable();
    glEnable(GL_LIGHTING);
    
    camera.begin();
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofSetLineWidth(0.3);
    ofSetColor(garallyColor);
    ofRotateX(90);
    if(garallyStripMode == 1){
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, pattern[spentFrames/10 % 8]);
        garallyModelDrawer.drawModel(0);
        glDisable(GL_LINE_STIPPLE);
    }else if(garallyStripMode == 0){
        garallyModelDrawer.drawModel(0);
    }else if(garallyStripMode == 2){
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, pattern[0]);
        garallyModelDrawer.drawModel(0);
        glDisable(GL_LINE_STIPPLE);
    }
    if(drawNetworkLineMode){
        ofSetColor(networkLineColor);
        ofSetLineWidth(5);
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(2, netLinePattern++);
        if(netLinePattern == 0xFFFF){
            netLinePattern = 0x0000;
        }
        networkLine.draw();
        glDisable(GL_LINE_STIPPLE);
    }
    ofSetLineWidth(1);
    ofSetColor(lineColor);
    ofLine(emitPoint, targetPoint);
    
    light.disable();
    glDisable(GL_LIGHTING);
    
    ofPopMatrix();
    ofPopStyle();
    camera.end();
}

void SpyMeshIntro::init(){
    
    trails = *new TrailRenderer(ofVec3f(ofGetWidth()/2 -ofGetWidth() * 5 ,ofGetHeight() * 1, 70),
                                ofVec3f(ofGetWidth()/2 + 400, ofGetHeight()/2,70));
    
    spentFrames = 0;
    initModelDrawer();
    initLineEmitPoints();
    gui.init();
    light.setPointLight();
    light.setAmbientColor(ofFloatColor(0.5, 0.5, 0.6, 1.0));
    light.setDiffuseColor(ofFloatColor(0.2, 1.0, 0.2));
    light.setSpecularColor(ofFloatColor(0, 0, 0));
    cameraRotateFrames = 300;
    cameraLookPoint = ofPoint(ofGetWidth()/2 + 400, ofGetHeight()/2,70);
    rotateFrame = 50;
    waitFrame = 100;
}

void SpyMeshIntro::initLineEmitPoints(){

    lineEmitPointDistance = 100000;
    lineEmitPoints[0] = ofVec3f(lineEmitPointDistance,lineEmitPointDistance,0);
    lineEmitPoints[1] = ofVec3f(- lineEmitPointDistance,lineEmitPointDistance,0);
    lineEmitPoints[2] = ofVec3f(lineEmitPointDistance,- lineEmitPointDistance,0);
    lineEmitPoints[3] = ofVec3f(-lineEmitPointDistance,- lineEmitPointDistance,0);
}

void SpyMeshIntro::initModelDrawer(){
    model.loadModel("garally.stl");
    for(int i = 0; i < model.getMeshCount(); i++){
        garallyModelDrawer.setVertices(model.getMesh(i).vertices, model.getMesh(i).getIndices(), 200.0);
    }
}

void SpyMeshIntro::reset(){
    spentFrames = 0;
    garallyModelDrawer.reset();
}

void SpyMeshIntro::onMouseDown(int x, int y){
}

void SpyMeshIntro::keyPressed(int key){
    switch (key) {
        case 'p':
            gui.drawCenterCircleMode = !gui.drawCenterCircleMode;
            break;
        case 'o':
            gui.drawGraphMode = !gui.drawGraphMode;
            break;
        case 'i':
            gui.drawTargetMarkerMode = !gui.drawTargetMarkerMode;
            break;
        case 'u':
            drawFPSAndSPFMode = !drawFPSAndSPFMode;
            break;
        case 'y':
            gui.drawClockMode = !gui.drawClockMode;
            break;
        case 't':
            garallyStripMode = (garallyStripMode + 1) % 3;
            break;
        case 'r':
            drawNetworkLineMode = !drawNetworkLineMode;
            break;
        case 'R':
            reset();
            break;
        default:
            break;
    }
}