//
//  SpyMesh.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#include "SpyMesh.h"

void SpyMesh::update(){
    
    float * val = ofSoundGetSpectrum(1);
    modelSize = val[0] * 1;

    if(isStarted){
        if(modelDrawMode){
            //本番TwitterStreamingAPi使用時
            /*if(JsonReceiver::recieve()){
             for(int i = 0; i < ADD_TRIANGLE_PER_TWEET; i++){
             cout << "true" << i << endl;;
             targetPoint = modelDrawer.addVertex((JsonReceiver::updateNum - 1) * ADD_TRIANGLE_PER_TWEET + i );
             }
             }*/
            
            //Debug用
            for(int i = 0; i < ADD_TRIANGLE_PER_UPDATE; i++){
                targetPoint = modelDrawer.addVertex(spentFrames * ADD_TRIANGLE_PER_UPDATE + i );
            }
            spentFrames+=1;
        }
        
        if(coloerMeshDrawMode){
            modelDrawer.changeColoredPartMesh();
            modelDrawer.updateColoredMesh(1.0 + modelSize);
        }
        
        if(int(ofGetElapsedTimeMillis() / 30) % 60 == 0){
            emitPoint = lineEmitPoints[int(ofRandom(0,6))];
            if(randomTrianlgeDrawMode) rtDrawer.changeMesh(15,9);
        }
        
    }else{
        wainingFrames++;
    }
    
    if(useRollCam){
        rollCam.update();
    }else{
        camera.setPosition(ofPoint(ofGetWidth()/2 + 300 * sin(float(ofGetElapsedTimef())/3.0) , ofGetHeight()/2 + 300 * cos(float(ofGetElapsedTimef())/3.0) , 150 + 250 * cos(float(ofGetElapsedTimef() / 10.0))));
        camera.lookAt(ofPoint(ofGetWidth()/2, ofGetHeight()/2,0));
    }
}

void SpyMesh::draw(){
    
    ofPushMatrix();
    ofPushStyle();
    
    if(useRollCam){
        rollCam.begin();
    }else{
        camera.begin();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    }

    ofSetColor(50, 255, 50 , 150);
    
    if(isStarted){
        ofSetLineWidth(0.3);
        if(modelDrawMode) {
            modelDrawer.drawModel(modelSize);
            drawEmitter();
            ofLine(emitPoint, targetPoint);
            sphere.drawSphere(emitPoint, (60.0 - float(spentFrames % 60)) / 60.0 * 0.1 + 0.05);
        }
        if(coloerMeshDrawMode) modelDrawer.drawColoredMesh();
        if(randomTrianlgeDrawMode) rtDrawer.drawTriangleMesh();
        ofDrawBitmapString(ofToString(spentFrames) + " FPS:"+ofToString(ofGetFrameRate()) ,emitPoint);
    }
    
    ofPopMatrix();
    ofPopStyle();
    
    if(useRollCam){
        rollCam.end();
    }else{
        camera.end();
    }
    
    ofPushStyle();
    ofSetColor(50, 255, 100);
    modelDrawer.drawPercentage();
    ofPopStyle();
}

void SpyMesh::drawEmitter(){

    ofPushStyle();

    ofSetColor(50, 255, 50,150);
    
    for(int i = 0; i < 6; i++){
        ofPushMatrix();
        ofRotateX(ofGetElapsedTimef() * (i + 1) * 2);
        ofRotateY(ofGetElapsedTimef() * (i + 1) * 2);
        ofRotateZ(ofGetElapsedTimef() * (i + 1) * 2);
        if(wainingFrames < 120){
            sphere.drawSphere(lineEmitPoints[i] * float(100 - wainingFrames), 0.15);
        }else{
            sphere.drawSphere(lineEmitPoints[i], 0.1 + 0.5 * modelSize);
        }
        ofPopMatrix();
    }
    ofPopStyle();
}

void SpyMesh::init(){
    
    ofBackground(0);
    ofDisableArbTex();
    isStarted = false;
    spentFrames = 0;
    wainingFrames = 0;
    SoundManager::play();
    initModelDrawer();
    initLineEmitPoints();
    JsonReceiver::init();
    rollCam.setup();
    rollCam.setCamSpeed(0.1);
    rollCam.setRandomScale(1.5, 2.0);
    rollCam.setRandomPos(360);
}

void SpyMesh::initLineEmitPoints(){
    
    lineEmitPointDistance = 600;
    lineEmitPoints[0] = ofVec3f(lineEmitPointDistance,lineEmitPointDistance,0);
    lineEmitPoints[1] = ofVec3f(- lineEmitPointDistance,lineEmitPointDistance,0);
    lineEmitPoints[2] = ofVec3f(lineEmitPointDistance,- lineEmitPointDistance,0);
    lineEmitPoints[3] = ofVec3f(-lineEmitPointDistance,- lineEmitPointDistance,0);
    lineEmitPoints[4] = ofVec3f(0,0,lineEmitPointDistance);
    lineEmitPoints[5] = ofVec3f(0,0,-lineEmitPointDistance);
}

void SpyMesh::initModelDrawer(){
    
    model.clear();
    modelDrawer.setPrimitiveMode(OF_PRIMITIVE_TRIANGLES);
    model.loadModel("MrT3ds/mrt.3ds");
    for(int i = model.getMeshCount() - 1; i > 4; i--){
        modelDrawer.setVertices(model.getMesh(i).vertices, model.getMesh(i).getIndices(), 1.1);
        rtDrawer.setVertices(model.getMesh(i).vertices, 1.1);
    }
    sphere = *new DrawerSphere(0.15);
}

void SpyMesh::onMouseDown(int x, int y){
    mouseX = x;
    mouseY = y;
    isStarted = true;
}

void SpyMesh::keyPressed(int key){
    switch (key) {
        case 'q':
            modelDrawMode = true;
            modelDrawer.setPrimitiveMode(OF_PRIMITIVE_TRIANGLES);
            break;
        case 'w':
            modelDrawMode = true;
            modelDrawer.setPrimitiveMode(OF_PRIMITIVE_LINE_LOOP);
            break;
        case 'e':
            modelDrawMode = true;
            modelDrawer.setPrimitiveMode(OF_PRIMITIVE_POINTS);
            break;
        case 'r':
            modelDrawMode = false;
            break;
        case 'a':
            coloerMeshDrawMode = true;
            modelDrawer.changeColoredMode(ModelDrawer::ColoredMeshMode::LINE);
            break;
        case 's':
            coloerMeshDrawMode = true;
            modelDrawer.changeColoredMode(ModelDrawer::ColoredMeshMode::RANDOM);
            break;
        case 'd':
            coloerMeshDrawMode = true;
            modelDrawer.changeColoredMode(ModelDrawer::ColoredMeshMode::AFFECTED_GLAVITY_GLASS);
            break;
        case 'f':
            coloerMeshDrawMode = false;
            break;
        case 'z':
            randomTrianlgeDrawMode = true;
            break;
        case 'x':
            rtDrawer.changeMesh(15, 9);
            break;
        case 'c':
            randomTrianlgeDrawMode = false;
            break;
        //CamSettings
        case '0':
            useRollCam = !useRollCam;
            break;
        case '1':
            rollCam.setRandomScale(1.5, 2.0);
            rollCam.setRandomPos(360);
            break;
        case '2':
            rollCam.setRandomPos(360);
            break;
        case '3':
            rollCam.setRandomScale(1.5, 2.0);
            break;
        case '4':
            rollCam.setPos(0, 0, 0);
            break;
        case '5':
            rollCam.setScale(1.2);
            break;
        default:
            break;
    }
}