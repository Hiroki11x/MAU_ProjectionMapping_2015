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
        iconFirstPosition[i] = ofVec3f(ofRandom(-800,800),ofRandom(-800,800),ofRandom(-800,800));
        iconFirstRotation[i] = ofVec3f(ofRandom(360),ofRandom(360),ofRandom(360));
        
        ofVec3f xDiff = (ofVec3f(8,0,0)).rotated(iconFirstRotation[i].x, iconFirstRotation[i].y, iconFirstRotation[i].z);
        ofVec3f yDiff = (ofVec3f(0,8,0)).rotated(iconFirstRotation[i].x, iconFirstRotation[i].y, iconFirstRotation[i].z);
        ofVec3f offset = iconFirstPosition[i].rotated(iconFirstRotation[i].x, iconFirstRotation[i].y, iconFirstRotation[i].z);
        
        for(int x = 0; x < ICON_SIZE; x++){
            for(int y = 0; y < ICON_SIZE; y++){
                iconPoints.at(i).addVertex( x * xDiff + y * yDiff + offset);
            }
        }
    }
    for(int i = 0; i< MAX_ICON * ICON_SIZE * ICON_SIZE; i++){
        downSpeed[i] = ofRandom(0.005, 0.015);
        targetPosition[i] = ofVec3f(400.0 * sin(360.0 * float(i)/float(MAX_ICON * ICON_SIZE * ICON_SIZE)),
                                    400.0 * cos(360.0 * float(i)/float(MAX_ICON * ICON_SIZE * ICON_SIZE)),
                                    0);
        Offset[i] = ofRandom(0, 80);
        
        collapseSpeed[i] = ofRandom(0, 0);
        collVecs[i] = ofVec3f(ofRandom(-10,10),ofRandom(-10,10),ofRandom(-10,10));
        
    }
    doorModel.loadModel("door2.obj");
    doorModel.setPosition(0, 0, 0);
    lastPosition = ofVec3f(0,ofGetHeight()/2 + 50,-5000);
    lastParticlePosition = ofVec3f(0,ofGetHeight()/2 - 200,-5000);
    mode = LoadIcon;
    spentFrames = 0;
    //cameraPosition = ofVec3f(0, ofGetHeight()/2, 600);
    ofEnableDepthTest();
    ofBackground(0);
    noiseElement = 0.0;
    iconNum = 0;
    spentFrames = 0;
    iconNum = 0;
    for(int x = -1000; x < 1000; x += 100){
        for(int y = -1000; y < 1000; y += 100){
            for(int z = -1000; z < 1000; z+=100){
                backGroundCrosses.addVertex(ofVec3f(x -10,y,z));
                backGroundCrosses.addVertex(ofVec3f(x +10,y,z));
                backGroundCrosses.addVertex(ofVec3f(x,y -10,z));
                backGroundCrosses.addVertex(ofVec3f(x,y +10,z));
                backGroundCrosses.addVertex(ofVec3f(x,y,z -10));
                backGroundCrosses.addVertex(ofVec3f(x,y,z +10));
                backGroundCrosses.addColor(crossColor);
                backGroundCrosses.addColor(crossColor);
                backGroundCrosses.addColor(crossColor);
                backGroundCrosses.addColor(crossColor);
                backGroundCrosses.addColor(crossColor);
                backGroundCrosses.addColor(crossColor);
            }
        }
    }
    backGroundCrosses.setMode(OF_PRIMITIVE_LINES);
    cameraPosition = ofVec3f(0,0,0);
    cameraLookPoint = ofVec3f(0,0,0);
    camera.setPosition(cameraPosition);
   // camera.lookAt(cameraLookPoint);
}

void IconStream::update(){
    updateCamera();
    updatePoint();
    spentFrames++;
    switch (mode) {
        case Collapse:
            for(int i = 0; i< MAX_ICON * ICON_SIZE * ICON_SIZE; i++){
                
                collapseSpeed[i] += ofRandom(0.48, 0.9);
                
            }
            break;
        case LoadIcon:
            loadIcon();
            break;
        case MakeCircle:
            if(spentFrames < 200) break;
            nextPhase();
            spentFrames = 0;
            for(int i = 0; i< MAX_ICON * ICON_SIZE * ICON_SIZE; i++){
                downSpeed[i] = ofRandom(0.01, 0.5);
            }
            break;
        case Convergence:
            //cameraPosition = cameraPosition + 0.01 * (lastPosition - cameraPosition);
            if(!(spentFrames > 200)) break;
            nextPhase();
            lastParticlePosition = ofVec3f(0,ofGetHeight()/2 - 300,-6000);
            spentFrames = 0;
            break;
        case RemakeCircle:
            if(spentFrames < 200) break;
            nextPhase();
            spentFrames = 0;
            for(int i = 0; i< MAX_ICON * ICON_SIZE * ICON_SIZE; i++){
                downSpeed[i] = ofRandom(10, 20);
            }
            break;
        case Down:
            if(spentFrames < 100) break;
            nextPhase();
            remakeFlag = true;
            spentFrames = 0;
            for(int i = 0; i< MAX_ICON * ICON_SIZE * ICON_SIZE; i++){
                downSpeed[i] = ofRandom(0.005, 0.008);
            }
            break;
        default:
            break;
    }
   // camera.setPosition(cameraPosition);
   // camera.lookAt(ofVec3f(0, ofGetHeight()/2,cameraPosition.z - 600));
    light.setPosition(0, ofGetHeight()/2,650);
    light.lookAt(ofVec3f(0, ofGetHeight()/2,0));
}

void IconStream::draw(){
    ofDisableDepthTest();
    ofDisableBlendMode();
    ofDisableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    ofEnableAlphaBlending();
    backShader.load("","shader.frag");
    backShader.begin();
    backShader.setUniform1f("u_time", ofGetElapsedTimef());
    backShader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    ofRect(0,0,ofGetWidth(), ofGetHeight());
    backShader.end();
    
    ofEnableDepthTest();
    camera.begin();
    //ofSetColor(crossColor);
    ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
    glPushMatrix();
    glRotatef(180, 0, 0, 1); //Need to reverce
    //glTranslatef(0, -600, 0);
    glPushMatrix();
    switch (mode) {
        case LoadIcon:
        case MoveCam:
            glPointSize(6);
            backGroundCrosses.draw();
            for(int i = 0; i < iconNum; i++){
                glPushMatrix();
                //glTranslatef((i/5 - 1) * 160, 0, 0);
                //glRotatef(72 * i + spentFrames, 0, 1, 0);
                /*ofTranslate(iconFirstPosition[i]);
                ofRotateX(iconFirstRotation[i].x);
                ofRotateY(iconFirstRotation[i].y);
                ofRotateZ(iconFirstRotation[i].z);*/
                iconPoints.at(i).draw();
                glPopMatrix();
            }
            break;
        case Collapse:
            ofPushMatrix();
            ofRotateX(boxRotation.x);
            ofRotateY(boxRotation.y);
            ofRotateZ(boxRotation.z);
            //ofSetColor(100, 255, 255,50);
            //ofDrawBox(-1000, -1000, -1000, 2000, 2000, 2000);
            glPointSize(6);
            backGroundCrosses.setMode(OF_PRIMITIVE_LINES);
            backGroundCrosses.draw();
            for(int i = 0; i < iconNum; i++){
                glPushMatrix();
                iconPoints.at(i).draw();
                glPopMatrix();
            }
            ofPopMatrix();
           
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
          /*  if(spentFrames < 400) {
                glPointSize(16 - spentFrames/40.0);
            }else {
                glPointSize(6);
            }*/
            for(int i = 0; i< MAX_ICON; i++){
                iconPoints.at(i).draw();
            }
            break;
        default:
            break;
    }glPopMatrix();
    glPopMatrix();
    camera.end();
    ofDisableBlendMode();
    ofDisableDepthTest();

    ofDisableAlphaBlending();
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

void IconStream::updateCamera(){

    switch (mode) {
        case LoadIcon:
            if((cameraPosition + (nextCameraPosition - befCameraPosition) / float(rotateFrame)).length() < 2000){
                cameraPosition += (nextCameraPosition - befCameraPosition) / float(rotateFrame);
                cameraLookPoint += (nextCameraLookPoint - befCameraLookPoint) / float(rotateFrame);
                camera.setPosition(cameraPosition);
                camera.lookAt(cameraLookPoint);
            }
            break;
        default:
            cameraRotateFrames++;
            if(cameraRotateFrames < cameraWaitFrame){
                 if(cameraRotateFrames < rotateFrame){
                     cameraPosition += (nextCameraPosition - befCameraPosition) / float(rotateFrame);
                     cameraLookPoint += (nextCameraLookPoint - befCameraLookPoint) / float(rotateFrame);
                     camera.setPosition(cameraPosition);
                     camera.lookAt(cameraLookPoint);
                 }
            }
            else{
                cameraRotateFrames = 0;
                befCameraPosition = cameraPosition;
                nextCameraPosition = ofVec3f(ofRandom(-500, 500),ofRandom(-500, 500),ofRandom(1000, 1500));
                befCameraLookPoint = cameraLookPoint;
                nextCameraLookPoint = ofPoint(ofRandom(-150,150),  ofRandom(-150, 150), ofRandom(0,200));
                cameraWaitFrame = ofRandom(50,100);
                rotateFrame = ofRandom(10,50);
            }
            break;
      /*  case Collapse:
            cameraPosition = ofVec3f(0,0,2500);
            cameraLookPoint = ofVec3f(0,0,0);
            camera.setPosition(cameraPosition);
            camera.lookAt(cameraLookPoint);
            break;
        case MoveCam:
            break;
        default:
            break;*/
    }
    
    
    
    //cameraRotateFrames++;
    //if(cameraRotateFrames < cameraWaitFrame){
   //     if(cameraRotateFrames < rotateFrame){
     //   }
// }
/*else{
        cameraRotateFrames = 0;
        befCameraPosition = cameraPosition;
        nextCameraPosition = ofVec3f(ofRandom(-500, 500),ofRandom(-500, 500),ofRandom(-500, 500));
        befCameraLookPoint = cameraLookPoint;
        nextCameraLookPoint = ofPoint(ofGetWidth()/2 + ofRandom(-500,500), ofGetHeight()/2 + ofRandom(-150, 150),70 + ofRandom(-500,500));
        cameraWaitFrame = ofRandom(50,100);
        rotateFrame = ofRandom(10,50);
    }*/
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
            case Collapse:
                collapse(w, h, x, y);
                break;
            case MakeCircle:
                noiseElement += 0.1;
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

void IconStream::collapse(int w, int h, int x, int y){
    
    //ofVec3f collvec = (ofVec3f(0,collapseSpeed[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE],0)).rotated(boxRotation.x, boxRotation.y, boxRotation.z);
    
   // collVecs[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] += (ofVec3f(0,ofRandom(0.1, 0.9),0)).rotated(boxRotation.x, boxRotation.y, boxRotation.z);
    //ofVec3f collvec = collVecs[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE];
    //collVecs[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE].y += 0.9 + ofRandom(0.1);
    ofVec3f collvec = collVecs[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE];
    float xStatus;
    float yStatus;
    float zStatus;
    
    if(iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).x - collvec.x > -950 && iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).x - collvec.x < 950){
       /* ofPoint p = ofPoint(iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).x - collvec.x,
                            iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).y,
                            iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).z);*/
    
        xStatus = 1.0;
        //iconPoints.at(w * SPY_ICON_SIZE + h).setVertex(y + x * ICON_SIZE, p);
    }else{
        collVecs[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE].x *= -1.0;
        xStatus = 0;
    }
    
    if(iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).y - collvec.y > -950.0 && iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).y - collvec.y < 950){
       // ofPoint p = ofPoint(iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x) - collvec);
        yStatus = 1.0;
      //  iconPoints.at(w * SPY_ICON_SIZE + h).setVertex(y + x * ICON_SIZE, p);
        
    }else{
        yStatus = 0;
        collVecs[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE].y *= -1.0;
    }
    
    if(iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).z - collvec.z > -950 && iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).z - collvec.z < 950){
        /*ofPoint p = ofPoint(iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).x ,
                            iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).y,
                            iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).z - collvec.z);
        iconPoints.at(w * SPY_ICON_SIZE + h).setVertex(y + x * ICON_SIZE, p);*/
        zStatus = 1.0;
        
    }else{
        zStatus = 0;
        collVecs[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE].z *= -1.0;
    }
    
    ofPoint p = ofPoint(iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).x - xStatus * collvec.x,
                        iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).y - yStatus * collvec.y,
                        iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x).z - zStatus * collvec.z);
    iconPoints.at(w * SPY_ICON_SIZE + h).setVertex(y + x * ICON_SIZE, p);
}

void IconStream::loadIcon(){
    if(putDammyData)loadDammyIcon();
    if(putRandomData) loadRandumIcon();
    if(!(iconNum < MAX_ICON)) return;
    if(!JsonReceiver::getInstance().checkIsNewData()) return;
    if(!newIcon.loadImage(JsonReceiver::getInstance().getUsersInfo().at(JsonReceiver::getInstance().updateNum - 1).iconURL)) return;
    
    newIcon.resize(ICON_SIZE, ICON_SIZE);
    for(int x = 0; x < newIcon.width; x++){
        for(int y = 0; y < newIcon.height; y++){
            //iconPoints.at(iconNum).addVertex(ofPoint(5 * x , 5 * y + 160 * (iconNum / 5), 0));
            //iconPoints.at(iconNum).addVertex(ofPoint(5 * x , 5 * y , 0));
            iconPoints.at(iconNum).addColor(newIcon.getColor(x, y));
        }
    }
    
 
    cameraRotateFrames = 0;
    befCameraPosition = cameraPosition;
    nextCameraPosition = iconPoints.at(iconNum).vertices.at(ICON_SIZE * ICON_SIZE /2) * 1.5;
    befCameraLookPoint = cameraLookPoint;
    nextCameraLookPoint = iconPoints.at(iconNum).vertices.at(ICON_SIZE * ICON_SIZE /2);
    cameraWaitFrame = ofRandom(50,100);
    rotateFrame = ofRandom(10,50);
    
    iconNum++;
    if(!(iconNum >= MAX_ICON)) return;
    //mode = MakeCircle;
    
    spentFrames = 0;
}

void IconStream::loadRandumIcon(){
    
    if(!(iconNum < MAX_ICON)) return;
    if(JsonReceiver::getInstance().updateNum == 0) return;
    newIcon.loadImage(JsonReceiver::getInstance().getUsersInfo().at(ofRandom(JsonReceiver::getInstance().updateNum)).iconURL);
    newIcon.resize(ICON_SIZE, ICON_SIZE);
    for(int x = 0; x < newIcon.width; x++){
        for(int y = 0; y < newIcon.height; y++){
            //iconPoints.at(iconNum).addVertex(ofPoint(5 * x , 5 * y + 160 * (iconNum / 5), 0));
            //iconPoints.at(iconNum).addVertex(ofPoint(5 * x , 5 * y , 0));
            iconPoints.at(iconNum).addColor(newIcon.getColor(x, y));
        }
    }
    cameraRotateFrames = 0;
    befCameraPosition = cameraPosition;
    nextCameraPosition = iconPoints.at(iconNum).vertices.at(ICON_SIZE * ICON_SIZE /2) * 1.5;
    befCameraLookPoint = cameraLookPoint;
    nextCameraLookPoint = iconPoints.at(iconNum).vertices.at(ICON_SIZE * ICON_SIZE /2);
    cameraWaitFrame = ofRandom(50,100);
    rotateFrame = ofRandom(10,50);
    
    iconNum++;
    putRandomData = false;
    if(!(iconNum >= MAX_ICON)) return;
    //mode = MakeCircle;
    
    spentFrames = 0;

}

void IconStream::loadDammyIcon(){
    if(!(iconNum < MAX_ICON)) return;
    newIcon = JsonReceiver::getInstance().getDammyImageData().at(ofRandom(5));
    newIcon.resize(ICON_SIZE, ICON_SIZE);
    for(int x = 0; x < newIcon.width; x++){
        for(int y = 0; y < newIcon.height; y++){
            //iconPoints.at(iconNum).addVertex(ofPoint(5 * x , 5 * y + 160 * (iconNum / 5), 0));
            //iconPoints.at(iconNum).addVertex(ofPoint(5 * x , 5 * y , 0));
            iconPoints.at(iconNum).addColor(newIcon.getColor(x, y));
        }
    }
    cameraRotateFrames = 0;
    befCameraPosition = cameraPosition;
    nextCameraPosition = iconPoints.at(iconNum).vertices.at(ICON_SIZE * ICON_SIZE /2) * 1.5;
    befCameraLookPoint = cameraLookPoint;
    nextCameraLookPoint = iconPoints.at(iconNum).vertices.at(ICON_SIZE * ICON_SIZE /2);
    cameraWaitFrame = ofRandom(50,100);
    rotateFrame = ofRandom(10,50);
    
    iconNum++;
    putDammyData = false;
    if(!(iconNum >= MAX_ICON)) return;
    //mode = MakeCircle;
    
    spentFrames = 0;
}

void IconStream::makeCircle(int w, int h, int x, int y){
    ofVec3f v = iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x) + downSpeed[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] * ((0.5 + 0.5 * ofNoise(noiseElement)) * targetPosition[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] - iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x));
    iconPoints.at(w * SPY_ICON_SIZE + h).setVertex(y + x * ICON_SIZE, v);

}

void IconStream::convergence(int w, int h, int x, int y){
    ofVec3f v = iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x) + downSpeed[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] * ((0.6 + 0.4 * ofNoise(x,y)) *lastParticlePosition + (0 + 0.5 * ofNoise(x,y)) * targetPosition[ (w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE]  - iconPoints.at(w * SPY_ICON_SIZE + h).vertices.at(y + ICON_SIZE * x));
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
    /*if(!JsonReceiver::getInstance().checkIsNewData()) return;
    if(!newIcon.loadImage(JsonReceiver::getInstance().getUsersInfo().at(JsonReceiver::getInstance().updateNum - 1).iconURL)) return;*/
    newIcon.loadImage("spy.png");
    newIcon.resize(ICON_SIZE * 4, ICON_SIZE * 4);
    for(int w = 0; w < SPY_ICON_SIZE; w++){
    for(int h = 0; h < SPY_ICON_SIZE; h++){
    for(int x = 0; x < ICON_SIZE; x++){
    for(int y = 0; y < ICON_SIZE; y++){
        remakeIconsColor[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] = newIcon.getColor(w * ICON_SIZE + x, h * ICON_SIZE + y);
       /* targetPosition[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] = ofVec3f((ICON_SIZE/2 - x) * 10 + (1 - w) * 10 * ICON_SIZE + 100,
                                                                                            -((ICON_SIZE/2 - y) * 10 + (- h) * 10 * ICON_SIZE) + ofGetHeight()/2 - 550,
                                                                                            -6000);*/
        targetPosition[(w * SPY_ICON_SIZE + h) * ICON_SIZE * ICON_SIZE + y + x * ICON_SIZE] = ofVec3f((ICON_SIZE/2 - x) * 10 + (2 - w) * 10 * ICON_SIZE ,
                                                                                                      -((ICON_SIZE/2 - y) * 10 + (2- h) * 10 * ICON_SIZE),
                                                                                                      0);
    }}}}
    remakeFlag = false;
}

void IconStream::nextPhase(){
    mode = (Mode)(mode + 1);
}

void IconStream::onMouseDown(int x, int y){}

void IconStream::keyPressed(int key){
    switch (key) {
        case 'P':
            putDammyData = true;
            break;
        case 'O':
            putRandomData = true;
            break;
        case 'R':
            init();
            break;
        case 'c':
            if(iconNum < MAX_ICON) break;
            mode = Collapse;
            break;
        case 'i':
            if(iconNum < MAX_ICON) break;
            mode = RemakeIcon;
            remakeFlag = true;
            break;
        case 'a':
            boxRotation.x += 3;
            if(boxRotation.x > 45){boxRotation.x = -45;}
            break;
        case 's':
            boxRotation.y += 3;
            if(boxRotation.y > 45){boxRotation.y = -45;}
            break;
        case 'd':
            boxRotation.z += 3;
            if(boxRotation.z > 45){boxRotation.z = -45;}
            break;
        case 'q':
            boxRotation.x -= 3;
            if(boxRotation.x < -45){boxRotation.x = 45;}
            break;
        case 'w':
            boxRotation.y -= 3;
            if(boxRotation.y < -45){boxRotation.y = 45;}
            break;
        case 'e':
            boxRotation.z -= 3;
            if(boxRotation.z < -45){boxRotation.z = 45;}
            break;
        default:
            break;
    }
    
}