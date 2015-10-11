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
        downSpeed[i] = ofRandom(3.0, 15.0);
    }
    rotationMode = true;
    
    doorModel.loadModel("door2.obj");
    doorModel.setPosition(0, 0, 0);
}

void IconStream::update(){
    if(iconNum < MAX_ICON){
        if(JsonReceiver::getInstance().checkIsNewData()){
            cout << JsonReceiver::getInstance().getUsersInfo().at(JsonReceiver::getInstance().updateNum - 1).iconURL << endl;
            if(newIcon.loadImage(JsonReceiver::getInstance().getUsersInfo().at(JsonReceiver::getInstance().updateNum - 1).iconURL)){
                newIcon.resize(ICON_SIZE, ICON_SIZE);
                for(int x = 0; x < newIcon.width; x++){
                    for(int y = 0; y < newIcon.height; y++){
                        iconPoints.at(iconNum).addVertex(ofPoint(5 * x , 5 * y + 160 * (iconNum / 6), 0));
                        iconPoints.at(iconNum).addColor(newIcon.getColor(x, y));
                    }
                }
                iconNum++;
            }
        }
    }else{
        for(int i = 0; i< MAX_ICON; i++){
            for(int x = 0; x < ICON_SIZE; x++){
                for(int y = 0; y < ICON_SIZE; y++){
                    if(iconPoints.at(i).vertices.at(y + ICON_SIZE * x).y + downSpeed[ i * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] < ofGetHeight() - 50){
                        ofPoint p = ofPoint(iconPoints.at(i).vertices.at(y + ICON_SIZE * x).x,
                                            iconPoints.at(i).vertices.at(y + ICON_SIZE * x).y + downSpeed[ i * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE],
                                            iconPoints.at(i).vertices.at(y + ICON_SIZE * x).z);
                        iconPoints.at(i).setVertex(y + x * ICON_SIZE, p);
                    }
                }
            }
        }
    }
    rotation++;
    /*if(doorDeg < 90){
        doorDeg++;
    }*/
    spentFrames++;
    light.setPosition(0, ofGetHeight()/2, 650);
    light.lookAt(ofVec3f(0, ofGetHeight()/2,1));
    camera.setPosition(0, ofGetHeight()/2, 600);
    camera.lookAt(ofVec3f(0, ofGetHeight()/2,1));
}

void IconStream::draw(){
    camera.begin();
    glPushMatrix();
    glRotatef(180, 0, 0, 1); //よーわからんけど反転させなうまくいかん
    
    drawDoor(doorDeg);
    
    glTranslatef(0, -600, 0);
    glPointSize(4);
    
    if(rotationMode){
        for(int i = 0; i< MAX_ICON; i++){
            glPushMatrix();
            glRotatef(60 * i + rotation, 0, 1, 0);
            iconPoints.at(i).draw();
            glPopMatrix();
        }
    }
    
    glPopMatrix();
    camera.end();
}

void IconStream::drawDoor(float deg){
    glPushMatrix();
    glTranslatef(0, -400, -3000); //-が奥
    light.enable();
    light.draw();
    ofDrawBox(0, -10, 0, 520, 480, 1);
    glPushMatrix();
    glRotatef(180, 0, 0, 1);
    glTranslatef(270, 30,0);
    glRotatef(deg, 0, 1, 0);
    doorModel.setPosition(-150, 0, 0);
    doorModel.draw(ofPolyRenderMode::OF_MESH_FILL);
    glRotatef(180, 0, 0, 1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(270, 0,0);
    glRotatef(deg, 0, 1, 0);
    doorModel.setPosition(-150, 0, 0);
    doorModel.draw(ofPolyRenderMode::OF_MESH_FILL);
    glPopMatrix();
    light.disable();
    glDisable(GL_LIGHTING);
    glPopMatrix();
}


void IconStream::onMouseDown(int x, int y){}

void IconStream::keyPressed(int key){
    if(key == 'p'){
        doorDeg = 0;
    }
}