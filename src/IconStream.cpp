//
//  IconStream.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/11.
//
//
#include "IconStream.h"

void IconStream::init(){
    iconPoints = *new vector<ofVboMesh>(MAX_ICON);
    for(int i = 0; i< MAX_ICON; i++){
        iconPoints.at(i).setMode(ofPrimitiveMode::OF_PRIMITIVE_POINTS);
    }
    for(int i = 0; i< MAX_ICON * ICON_SIZE * ICON_SIZE; i++){
        downSpeed[i] = ofRandom(0.005, 0.015);
        targetPosition[i] = ofVec3f(400.0 * sin(360.0 * float(i)/float(MAX_ICON * ICON_SIZE * ICON_SIZE)),
                                    400.0 * cos(360.0 * float(i)/float(MAX_ICON * ICON_SIZE * ICON_SIZE)),
                                    0);
    }
    doorModel.loadModel("door2.obj");
    doorModel.setPosition(0, 0, 0);
    lastPosition = ofVec3f(0,ofGetHeight()/2 + 50,-5000);
    lastParticlePosition = ofVec3f(0,ofGetHeight()/2 - 200,-5000);
    mode = LoadIcon;
    doorDeg = 0;
    spentFrames = 0;
    cameraPosition = ofVec3f(0, ofGetHeight()/2, 600);
    ofEnableDepthTest();
    ofBackground(0);
}

void IconStream::update(){
    
    updatePoint();
    spentFrames++;
    
    switch (mode) {
        case LoadIcon:
            loadIcon();
            break;
        case MakeCircle:
            if(spentFrames > 600){
                nextPhase();
                spentFrames = 0;
                for(int i = 0; i< MAX_ICON * ICON_SIZE * ICON_SIZE; i++){
                    downSpeed[i] = ofRandom(0.01, 0.5);
                }
            }
            break;
        case Convergence:
            cameraPosition = cameraPosition + 0.01 * (lastPosition - cameraPosition);
            if(spentFrames > 100){
                if(doorDeg < 100) doorDeg+=0.5;
            }
            if(spentFrames > 350){
                nextPhase();
                lastParticlePosition = ofVec3f(0,ofGetHeight()/2 - 300,-6000);
                spentFrames = 0;
            }
            break;
        case RemakeCircle:
            if(spentFrames > 200){
                nextPhase();
                spentFrames = 0;
                for(int i = 0; i< MAX_ICON * ICON_SIZE * ICON_SIZE; i++){
                    downSpeed[i] = ofRandom(10, 20);
                }
            }
            break;
        case Down:
            if(spentFrames > 100){
                nextPhase();
                remakeFlag = true;
                spentFrames = 0;
                for(int i = 0; i< MAX_ICON * ICON_SIZE * ICON_SIZE; i++){
                    downSpeed[i] = ofRandom(0.005, 0.008);
                }
            }
            break;
        default:
            break;
    }
    camera.setPosition(cameraPosition);
    camera.lookAt(ofVec3f(0, ofGetHeight()/2,cameraPosition.z - 600));
    light.setPosition(0, ofGetHeight()/2,650);
    light.lookAt(ofVec3f(0, ofGetHeight()/2,0));
}

void IconStream::draw(){
    camera.begin();
    glPushMatrix();
    glRotatef(180, 0, 0, 1); //Need to reverce
    glTranslatef(0, -600, 0);
    glPushMatrix();
    switch (mode) {
        case LoadIcon:
            glPointSize(4);
            for(int i = 0; i < MAX_ICON; i++){
                glPushMatrix();
                glTranslatef((i/5 - 1) * 160, 0, 0);
                glRotatef(72 * i + spentFrames, 0, 1, 0);
                iconPoints.at(i).draw();
                glPopMatrix();
            }
            break;
        case MakeCircle:
            glPointSize(4 + float(spentFrames)/50.0);
            glTranslatef(0, 200, 0);
            glRotatef(spentFrames, 0, 0, 1);
            for(int i = 0; i< MAX_ICON; i++){
                iconPoints.at(i).draw();
            }
            break;
        case Convergence:
        case RemakeCircle:
        case Down:
            glPointSize(16 + float(spentFrames)/100.0);
            for(int i = 0; i< MAX_ICON; i++){
                iconPoints.at(i).draw();
            }
            break;
        case RemakeIcon:
            if(spentFrames < 400) {
                glPointSize(16 - spentFrames/40.0);
            }else {
                glPointSize(6);
            }
            for(int i = 0; i< MAX_ICON; i++){
                iconPoints.at(i).draw();
            }
            break;
        default:
            break;
    }glPopMatrix();
    glPopMatrix();
    camera.end();
}

void IconStream::drawDoor(float deg){
    ofPushStyle();
    glPushMatrix();
    glTranslatef(0, -400, -5000);
    light.enable();
    light.draw();
    ofSetColor(50,255,50);
    glPushMatrix();
    glRotatef(180, 0, 0, 1);
    glTranslatef(270, 30,0);
    glRotatef(deg, 0, 1, 0);
    doorModel.setPosition(-150, 0, 0);
    doorModel.draw(ofPolyRenderMode::OF_MESH_WIREFRAME);
    glRotatef(180, 0, 0, 1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(270, 0,0);
    glRotatef(deg, 0, 1, 0);
    doorModel.setPosition(-150, 0, 0);
    doorModel.draw(ofPolyRenderMode::OF_MESH_WIREFRAME);
    glPopMatrix();
    light.disable();
    glDisable(GL_LIGHTING);
    glPopMatrix();
    ofPopStyle();
}

void IconStream::updatePoint(){
    if(mode == RemakeIcon && remakeFlag){
        loadSpyIcon();
        return;
    }
    for(int w = 0; w < SPY_ICON_SIZE; w++){
    for(int h = 0; h < SPY_ICON_SIZE; h++){
    for(int x = 0; x < ICON_SIZE; x++){
    for(int y = 0; y < ICON_SIZE; y++){
        switch (mode) {
            case MakeCircle:
                makeCircle(w, h, x, y);
                break;
            case Convergence:
                convergence(w, h, x, y);
                break;
            case RemakeCircle:
                remakeCircle(w, h, x, y);
                break;
            case Down:
                down(w, h, x, y);
                break;
            case RemakeIcon:
                remake(w, h, x, y);
                break;
            default:
                break;
        }
    }}}}
}

void IconStream::loadIcon(){
    if(!JsonReceiver::getInstance().checkIsNewData()) return;
    if(!newIcon.loadImage(JsonReceiver::getInstance().getUsersInfo().at(JsonReceiver::getInstance().updateNum - 1).iconURL)) return;
    
    newIcon.resize(ICON_SIZE, ICON_SIZE);
    for(int x = 0; x < newIcon.width; x++){
        for(int y = 0; y < newIcon.height; y++){
            iconPoints.at(iconNum).addVertex(ofPoint(5 * x , 5 * y + 160 * (iconNum / 5), 0));
            iconPoints.at(iconNum).addColor(newIcon.getColor(x, y));
        }
    }
    iconNum++;
    if(iconNum >= MAX_ICON ){
        mode = MakeCircle;
        spentFrames = 0;
    }
}

void IconStream::makeCircle(int w, int h, int x, int y){
    ofVec3f v = iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x) + downSpeed[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] * (targetPosition[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] - iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x));
    iconPoints.at(w * SPY_ICON_SIZE + h).setVertex(y + x * ICON_SIZE, v);

}

void IconStream::convergence(int w, int h, int x, int y){
    ofVec3f v = iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x) + downSpeed[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] *( lastParticlePosition + 0.2 * targetPosition[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE]  - iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x));
    iconPoints.at(w * SPY_ICON_SIZE + h).setVertex(y + x * ICON_SIZE, v);
}

void IconStream::remakeCircle(int w, int h, int x, int y){
    ofVec3f v = iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x) + downSpeed[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] * ( lastParticlePosition + 0.8 * targetPosition[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE]  - iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x));
    iconPoints.at(w * SPY_ICON_SIZE + h).setVertex(y + x * ICON_SIZE, v);
}

void IconStream::down(int w, int h, int x, int y){

    if(iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).y + downSpeed[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] > ofGetHeight() - 50) return;
    ofPoint p = ofPoint(iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).x,
                        iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).y + downSpeed[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE],
                        iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).z);
    iconPoints.at(w * SPY_ICON_SIZE + h).setVertex(y + x * ICON_SIZE, p);
}

void IconStream::remake(int w, int h, int x, int y){
    ofVec3f v = iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x) + downSpeed[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] *( targetPosition[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] - iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x));
    iconPoints.at(w * SPY_ICON_SIZE + h).setVertex(y + x * ICON_SIZE, v);
    
    ofColor c = iconPoints.at(w * SPY_ICON_SIZE + h).colors.at(y + ICON_SIZE * x);
    c.r += downSpeed[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] * float(remakeIconsColor[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE].r - c.r);
    c.g += downSpeed[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] * float(remakeIconsColor[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE].g - c.g);
    c.b += downSpeed[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] * float(remakeIconsColor[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE].b - c.b);
    iconPoints.at(w * SPY_ICON_SIZE + h).setColor(y + x * ICON_SIZE, c);
}

void IconStream::loadSpyIcon(){
    if(!JsonReceiver::getInstance().checkIsNewData()) return;
    if(!newIcon.loadImage(JsonReceiver::getInstance().getUsersInfo().at(JsonReceiver::getInstance().updateNum - 1).iconURL)) return;
    newIcon.loadImage("spy.png");
    newIcon.resize(ICON_SIZE * 4, ICON_SIZE * 4);
    for(int w = 0; w < SPY_ICON_SIZE; w++){
    for(int h = 0; h < SPY_ICON_SIZE; h++){
    for(int x = 0; x < ICON_SIZE; x++){
    for(int y = 0; y < ICON_SIZE; y++){
        remakeIconsColor[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] = newIcon.getColor(w * ICON_SIZE + x, h * ICON_SIZE + y);
        targetPosition[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] = ofVec3f((ICON_SIZE/2 - x) * 10 + (1 - w) * 10 * ICON_SIZE + 100,
                                                                                            -((ICON_SIZE/2 - y) * 10 + (- h) * 10 * ICON_SIZE) + ofGetHeight()/2 - 550,
                                                                                            -6000);
    }}}}
    remakeFlag = false;
}

void IconStream::nextPhase(){
    mode = (Mode)(mode + 1);
}

void IconStream::onMouseDown(int x, int y){}

void IconStream::keyPressed(int key){
    if(key == 'p'){
        init();
    }
}