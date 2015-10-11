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
    rotationMode = true;
    drawWhiteRect = true;
    doorModel.loadModel("door2.obj");
    doorModel.setPosition(0, 0, 0);
    lastPosition = ofVec3f(0,ofGetHeight()/2 + 50,-5000);
    lastParticlePosition = ofVec3f(0,ofGetHeight()/2 - 200,-5000); //yは上が正
    mode = LoadIcon;
    doorDeg = 0;
    spentFrames = 0;
    cameraPosition = ofVec3f(0, ofGetHeight()/2, 600);
    ofEnableDepthTest();
    ofBackground(0);
}

void IconStream::update(){
    if(mode == LoadIcon){
        if(JsonReceiver::getInstance().checkIsNewData()){
            if(newIcon.loadImage(JsonReceiver::getInstance().getUsersInfo().at(JsonReceiver::getInstance().updateNum - 1).iconURL)){
                newIcon.resize(ICON_SIZE, ICON_SIZE);
                for(int x = 0; x < newIcon.width; x++){
                    for(int y = 0; y < newIcon.height; y++){
                        iconPoints.at(iconNum).addVertex(ofPoint(5 * x , 5 * y + 160 * (iconNum / 6), 0));
                        iconPoints.at(iconNum).addColor(newIcon.getColor(x, y));
                    }
                }
                iconNum++;
                if(iconNum >= MAX_ICON ){
                    mode = MakeCircle;
                    spentFrames = 0;
                }
            }
        }
    }else if(mode == MakeCircle){
        for(int i = 0; i< MAX_ICON; i++){
            for(int x = 0; x < ICON_SIZE; x++){
                for(int y = 0; y < ICON_SIZE; y++){
                    
                    ofVec3f v = iconPoints.at(i).vertices.at(y + ICON_SIZE * x) + downSpeed[ i * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] *( targetPosition[ i * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] - iconPoints.at(i).vertices.at(y + ICON_SIZE * x));
                    iconPoints.at(i).setVertex(y + x * ICON_SIZE, v);
                
                }
            }
        }
        spentFrames++;
        if(spentFrames > 600){
            mode = Convergence;
            spentFrames = 0;
            for(int i = 0; i< MAX_ICON * ICON_SIZE * ICON_SIZE; i++){
                downSpeed[i] = ofRandom(0.01, 0.5);
            }
        }
    }else if (mode == Convergence){
        for(int i = 0; i< MAX_ICON; i++){
            for(int x = 0; x < ICON_SIZE; x++){
                for(int y = 0; y < ICON_SIZE; y++){
                    
                    ofVec3f v = iconPoints.at(i).vertices.at(y + ICON_SIZE * x) + downSpeed[ i * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] *( lastParticlePosition + 0.2 * targetPosition[ i * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE]  - iconPoints.at(i).vertices.at(y + ICON_SIZE * x));
                    iconPoints.at(i).setVertex(y + x * ICON_SIZE, v);
                }
            }
        }
        spentFrames++;
        if(spentFrames > 200){
            if(doorDeg < 100){
                doorDeg+=0.5;
            }
        }
        if(spentFrames > 300){
            ofBackground(255);
            drawWhiteRect = false;
        }
        if(spentFrames > 350){
            mode = End;
            lastParticlePosition = ofVec3f(0,ofGetHeight()/2 - 300,-6000);
            spentFrames = 0;
        }
    }else if (mode == End){
        
        for(int i = 0; i< MAX_ICON; i++){
            for(int x = 0; x < ICON_SIZE; x++){
                for(int y = 0; y < ICON_SIZE; y++){
                    ofVec3f v = iconPoints.at(i).vertices.at(y + ICON_SIZE * x) + downSpeed[ i * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] * ( lastParticlePosition + 0.2 * targetPosition[ i * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE]  - iconPoints.at(i).vertices.at(y + ICON_SIZE * x));
                    iconPoints.at(i).setVertex(y + x * ICON_SIZE, v);
                }
            }
        }
        spentFrames++;
        if(spentFrames > 200){
            mode = Down;
            spentFrames = 0;
            for(int i = 0; i< MAX_ICON * ICON_SIZE * ICON_SIZE; i++){
                downSpeed[i] = ofRandom(10, 20);
            }
        }
        cout << spentFrames << endl;
    }else if (mode == Down){
        
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
    
    if(mode == Convergence){
        cameraPosition = cameraPosition + 0.01 * (lastPosition - cameraPosition);
    }
    
    camera.setPosition(cameraPosition);
    camera.lookAt(ofVec3f(0, ofGetHeight()/2,cameraPosition.z - 600));
    light.setPosition(0, ofGetHeight()/2,650);
    light.lookAt(ofVec3f(0, ofGetHeight()/2,0));

}

void IconStream::draw(){
    camera.begin();
    glPushMatrix();
    glRotatef(180, 0, 0, 1); //よーわからんけど反転させなうまくいかん
    
    drawDoor(doorDeg);
    
    glTranslatef(0, -600, 0);
   
    if(mode == LoadIcon){
         glPointSize(4);
        for(int i = 0; i< MAX_ICON/3; i++){
            glPushMatrix();
            glTranslatef(-160, 0, 0);
            glRotatef(60 * i + rotation, 0, 1, 0);
            iconPoints.at(i).draw();
            glPopMatrix();
        }
        for(int i = MAX_ICON/3; i< MAX_ICON/3*2; i++){
            glPushMatrix();
            glRotatef(60 * i + rotation, 0, 1, 0);
            iconPoints.at(i).draw();
            glPopMatrix();
        }
        for(int i = MAX_ICON/3*2; i< MAX_ICON; i++){
            glPushMatrix();
            glTranslatef(160, 0, 0);
            glRotatef(60 * i + rotation, 0, 1, 0);
            iconPoints.at(i).draw();
            glPopMatrix();
        }
    }else if(mode == MakeCircle){
        glPointSize(4 + float(spentFrames)/50.0);
        glPushMatrix();
        glTranslatef(0, 200, 0);
        glRotatef(rotation, 0, 0, 1);
        for(int i = 0; i< MAX_ICON; i++){
            iconPoints.at(i).draw();
        }
        glPopMatrix();
    }else if(mode == Convergence || mode == End || mode == Down){
        glPointSize(16 + float(spentFrames)/100.0);
        glPushMatrix();
       // glTranslatef(0, 200, 0);
       // glRotatef(rotation, 0, 0, 1);
        for(int i = 0; i< MAX_ICON; i++){
            iconPoints.at(i).draw();
        }
        glPopMatrix();
    }
    
    glPopMatrix();
    camera.end();
}

void IconStream::drawDoor(float deg){
    glPushMatrix();
    glTranslatef(0, -400, -5000); //-が奥
    light.enable();
    light.draw();
    if(drawWhiteRect) {
        ofPushStyle();
        //ofSetColor(0);
        ofDrawBox(0, -10, 0, 520, 480, 1);
        ofPopStyle();
    }
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