//
//  SpyMesh.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#include "SpyMesh.h"

void SpyMesh::update(){
    if(endAnalyze) vPlayer.update();
    gui.updateGui();
    float * val = ofSoundGetSpectrum(1);
    modelSize = val[0] * 1;
    if(JsonReceiver::getInstance().checkIsNewData()){
        agents.push_back(*new AgentAnalysis(lineEmitPoints[int(ofRandom(6))], JsonReceiver::getInstance().getUserNames().at(JsonReceiver::getInstance().updateNum - 1)));
        agentNum++;
    }
    //----------------------------------------------------------------------
    //Dammy
    if(agentDebug){
        agents.push_back(*new AgentAnalysis(lineEmitPoints[int(ofRandom(6))],
                                            JsonReceiver::getInstance().getDammyUserNameData().at(ofRandom(8))));
        agentDebug = false;
        agentNum++;
    }
    
    if(putRandumData){
        if(JsonReceiver::getInstance().updateNum != 0){
            agents.push_back(*new AgentAnalysis(lineEmitPoints[int(ofRandom(6))],
                                            JsonReceiver::getInstance().getUserNames().at(ofRandom(JsonReceiver::getInstance().updateNum))));
        }
        putRandumData = false;
        agentNum++;
    }
    
    //-----------------------------------------------------------------------
    updateVertices();
    
    if(coloerMeshDrawMode){
        modelDrawer.changeColoredPartMesh();
        modelDrawer.updateColoredMesh(1.0 + modelSize);
    }
    if(int(ofGetElapsedTimeMillis() / 30) % 60 == 0){
        emitPoint = lineEmitPoints[int(ofRandom(0,6))];
        if(randomTrianlgeDrawMode) rtDrawer.changeMesh(15,9);
        if(randomExpandMeshDrawMode) modelDrawer.changeRandomExpandMesh();
    }
    spentFrames+=1;
    
    if(useRollCam){
        rollCam.update();
        if(spentFrames % 40 == 0){
            rollCam.setRandomScale(2.0, 3.0);
            rollCam.setRandomPos(360);
        }
    }else{
      /*  camera.setPosition(ofPoint(ofGetWidth()/2 + 300 * sin(float(ofGetElapsedTimef())/3.0) , ofGetHeight()/2 + 300 * cos(float(ofGetElapsedTimef())/3.0) , 150 + 250 * cos(float(ofGetElapsedTimef() / 10.0))));*/
        camera.setPosition(ofPoint(ofGetWidth()/2 + 200 * sin(float(ofGetElapsedTimef())/3.0) , ofGetHeight()/2 + 200 * cos(float(ofGetElapsedTimef())/3.0) , 150 + 150 * cos(float(ofGetElapsedTimef() / 10.0))));
        camera.lookAt(ofPoint(ofGetWidth()/2, ofGetHeight()/2,0));

        light.setPosition(ofPoint(ofGetWidth()/2 + 300 * sin(float(ofGetElapsedTimef())/3.0) , ofGetHeight()/2 + 300 * cos(float(ofGetElapsedTimef())/3.0) , 150 + 250 * cos(float(ofGetElapsedTimef() / 10.0))));
        light.lookAt(ofPoint(ofGetWidth()/2, ofGetHeight()/2,0));
    }
}

void SpyMesh::updateVertices(){
    if(spentFrames % 6 != 0) return;
    //if(spentFrames % 3 != 0) return;
    for(int n = 0; n < agents.size(); n++){
        for(float f = 0; f < 1; f+= agents.at(n).eraseSpeed){
            agents.at(n).removeVertices();
        }
        if(agents.at(n).removeVertices()){
            agents.at(n).targetPodsition = modelDrawer.addVertex();
        }else{
            agents.erase(agents.begin() + n);
            n--;
        }
    }
}

void SpyMesh::draw(){
    ofDisableDepthTest();
    ofDisableBlendMode();
    ofDisableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnableAlphaBlending();
    ofSetLineWidth(3);
    if(!trailMode){
        backShader.load("","shader.frag");
        backShader.begin();
        backShader.setUniform1f("u_time", ofGetElapsedTimef());
        backShader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
        ofRect(0,0,ofGetWidth(), ofGetHeight());
        backShader.end();
    }
    
    if(!endAnalyze) gui.drawGui(agents);

    ofPushMatrix();
    ofPushStyle();
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    if(trailMode){
        ofDisableDepthTest();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofEnableAlphaBlending();
        //ofSetColor(0, 0, 0, 10);
        ofSetColor(0, 0, 0, 5);
        ofFill();
        ofRect(0,0, ofGetWidth(), ofGetHeight());
    }else{
        ofEnableDepthTest();
    }
    
    if(useRollCam){
        rollCam.begin();
    }else{
        camera.begin();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    }
    

    ofSetLineWidth(0.3);
    if(modelDrawMode) {
        ofSetColor(spyModelColor);
        modelDrawer.drawModel(modelSize);
        ofSetColor(emitterColor);
        if(!endAnalyze) drawEmitter();
    }
    if(coloerMeshDrawMode) modelDrawer.drawColoredMesh();  //SetColorInClass
    if(randomTrianlgeDrawMode) {
        rtDrawer.drawTriangleMesh();  //SetColorInClass
        ofSetColor(spiralModelColor);
        spiralDrawer.drawSpiral(modelSize);
    }
    
    if(garallyDrawMode){
        ofSetColor(garallyModelColor);
        garallyDrawer.drawGarally();
    }

    ofSetColor(randomExpandMeshColor);
    if(randomExpandMeshDrawMode) modelDrawer.drawRandomExpandMesh(modelSize);

    ofPopMatrix();
    ofPopStyle();
    
    if(useRollCam){
        rollCam.end();
    }else{
        camera.end();
    }
    ofPushStyle();
    ofDisableDepthTest();
    modelDrawer.drawPercentage(); //SetColorInClass
    ofSetColor(255);
    if(endAnalyze){
        vPlayer.draw(ofGetWidth()/2 - vPlayer.width/2, ofGetHeight()/2 - vPlayer.height/2, vPlayer.width, vPlayer.height);
    }
    ofPopStyle();
}

void SpyMesh::drawEmitter(){

    ofPushStyle();
    for(int i = 0; i < agents.size(); i++){
        ofPushMatrix();
        agents.at(i).drawAgent();
        ofPopMatrix();
    }
    ofPopStyle();
}

void SpyMesh::init(){
    
    ofBackground(0);
    ofDisableArbTex();
    spentFrames = 0;
    wainingFrames = 0;
    SoundManager::play();
    initModelDrawer();
    initLineEmitPoints();
    light.setup();
    rollCam.setup();
    rollCam.setCamSpeed(0.1);
    rollCam.setRandomScale(1.5, 2.0);
    rollCam.setRandomPos(360);
    spiralDrawer = *new SpiralDrawer();
    spiralDrawer.init(2000.0);
    garallyDrawer = *new GarallyDrawer();
    garallyDrawer.init();
    gui = *new SpyMeshSceneGui();
    gui.init();
    vPlayer.loadMovie("complete.mp4");
}

void SpyMesh::initLineEmitPoints(){
    
    lineEmitPointDistance = 150;
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

void SpyMesh::changeColorSet(){
    colorSetIndex = (colorSetIndex + 1) % 3;
    switch (colorSetIndex) {
        case 0: //BlueBase
            //spyModelColor = ofColor(50, 255, 200 , 150);
            spyModelColor = ofColor(50, 255, 200 , 255);
            emitterColor = ofColor(50, 255, 200,150);
            spiralModelColor = ofColor(0,153,204,150);
            garallyModelColor = ofColor(204, 255, 255, 150);
            randomExpandMeshColor = ofColor(50, 255, 200 , 150);
            //-----------------------------------------------------
            //GUI
            //-----------------------------------------------------
            gui.agentNameColor = ofColor(220, 220, 255, 255);
            gui.agentBarColor = ofColor(255,0,102,200);
            gui.agentEntryFrameColor = ofColor(204,255,255,50);
            gui.agentEntryBackColor = ofColor(10,10,18,200);
            gui.agentEntryNewWaveColor = ofColor(100, 100, 200,100);
            gui.agentAnalistLineColor = ofColor(255,0,102, 100);
            gui.agentAnalistColor = ofColor(220, 220, 255, 255);
            gui.dnaFrameColor = ofColor(204,255,255,50);
            gui.dnaBackColor = ofColor(10,10,18,200);
            gui.dnaModelColor = ofColor(200,255,200,200);
            gui.waveFrameColor = ofColor(204,255,255,50);
            gui.waveBackColor = ofColor(10,10,18,200);
            gui.waveColor = ofColor(51,255,102);
            gui.foundInsideColor = ofColor(70, 170, 255,50);
            gui.foundMiddleColor = ofColor(200, 245, 240,50);
            gui.foundOutsideColor = ofColor(100, 200, 200,50);
            modelDrawer.parsentFrameColor = ofColor(51,153,204,100);
            modelDrawer.parsentColor = ofColor(204,255,255,200);
            rtDrawer.rtColor = ofColor(153,204,255, 200);
            rtDrawer.rtTransColor = ofColor(153,204,255, 50);
            break;
        case 1: //GreenBase
            //spyModelColor = ofColor(50, 255, 50, 150);
            spyModelColor = ofColor(50, 255, 50, 255);
            emitterColor = ofColor(50, 255, 50,150);
            spiralModelColor = ofColor(50, 255, 50,150);
            garallyModelColor = ofColor(204, 255, 255, 150);
            randomExpandMeshColor = ofColor(50, 255, 60, 150);
            //-----------------------------------------------------
            //GUI
            //-----------------------------------------------------
            gui.agentNameColor = ofColor(210, 255, 210,220);
            gui.agentBarColor = ofColor(51,102,255);
            gui.agentEntryFrameColor = ofColor(80,120,80,100);
            gui.agentEntryBackColor = ofColor(10,18,10,200);
            gui.agentEntryNewWaveColor = ofColor(100, 255, 100,100);
            gui.agentAnalistLineColor = ofColor(255, 255, 255, 100);
            gui.agentAnalistColor = ofColor(51,102,255, 150);
            gui.dnaFrameColor = ofColor(80,120,80,100);
            gui.dnaBackColor = ofColor(10,18,10,200);
            gui.dnaModelColor = ofColor(200,255,200,200);
            gui.waveFrameColor = ofColor(80,120,80,100);
            gui.waveBackColor = ofColor(10,18,10,200);
            gui.waveColor = ofColor(255,0,102,200);
            gui.foundInsideColor = ofColor(70, 255, 70,50);
            gui.foundMiddleColor = ofColor(60, 245, 60,50);
            gui.foundOutsideColor = ofColor(100, 255, 100,50);
            modelDrawer.parsentFrameColor = ofColor(80,120,80,100);
            modelDrawer.parsentColor = ofColor(50,255,50,200);
            rtDrawer.rtColor = ofColor(50, 200, 50, 200);
            rtDrawer.rtTransColor = ofColor(50, 255, 50, 50);
            break;
        case 2: //RedBase
            //spyModelColor = ofColor(255, 50, 255, 150);
            spyModelColor = ofColor(255, 50, 255, 255);
            emitterColor = ofColor(255, 50, 100,150);
            spiralModelColor = ofColor(255, 100, 255,150);
            garallyModelColor = ofColor(204, 255, 255, 150);
            randomExpandMeshColor = ofColor(200, 50, 200, 150);
            //-----------------------------------------------------
            //GUI
            //-----------------------------------------------------
            gui.agentNameColor = ofColor(210, 255, 210,220);
            gui.agentBarColor = ofColor(51,255,55);
            gui.agentEntryFrameColor = ofColor(120,80,80,100);
            gui.agentEntryBackColor = ofColor(10,18,10,200);
            gui.agentEntryNewWaveColor = ofColor(255, 100, 100,100);
            gui.agentAnalistLineColor = ofColor(255, 255, 255, 100);
            gui.agentAnalistColor = ofColor(200, 50, 255, 150);
            gui.dnaFrameColor = ofColor(120,80,80,100);
            gui.dnaBackColor = ofColor(18,10,10,200);
            gui.dnaModelColor = ofColor(255,200,200,200);
            gui.waveFrameColor = ofColor(120,80,80,100);
            gui.waveBackColor = ofColor(18,10,10,200);
            gui.waveColor = ofColor(51,102,255);
            gui.foundInsideColor = ofColor(255, 70, 70,50);
            gui.foundMiddleColor = ofColor(255, 60, 60,50);
            gui.foundOutsideColor = ofColor(255, 100, 100,50);
            modelDrawer.parsentFrameColor = ofColor(120,80,80,100);
            modelDrawer.parsentColor = ofColor(255,50, 50,200);
            rtDrawer.rtColor = ofColor(200, 50, 50, 200);
            rtDrawer.rtTransColor = ofColor(255, 50, 50, 50);
            break;
        default:
            break;
    }

}

void SpyMesh::onMouseDown(int x, int y){
    mouseX = x;
    mouseY = y;
}

void SpyMesh::reset(){
    modelDrawer.reset();
}

void SpyMesh::stop(){
    ofSetBackgroundAuto(true);
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
        case 'l':
            garallyDrawMode = !garallyDrawMode;
            break;
        case 'k':
            randomExpandMeshDrawMode = !randomExpandMeshDrawMode;
            break;
        case 'j':
            modelDrawer.changeRandomExpandMesh();
            break;
        case 'p':
            trailMode = !trailMode;
            ofSetBackgroundAuto(!trailMode);
            break;
        case 'y':
            gui.drawDNAmode = !gui.drawDNAmode;
            if(gui.drawDNAmode) gui.drawWaveMode = false;
            break;
        case 'u':
            gui.drawTargetLineMode = !gui.drawTargetLineMode;
            break;
        case 'i':
            gui.addWave();
            break;
        case 'o':
            gui.eraseWave();
            break;
        case 'g':
            gui.drawWaveMode = !gui.drawWaveMode;
            if(gui.drawWaveMode) gui.drawDNAmode = false;
            break;
            //CamSettings
        case 'Y':
            useRollCam = !useRollCam;
            break;
       /* case 'U':
            rollCam.setRandomScale(1.0, 2.0);
            rollCam.setRandomPos(360);
            break;
        case 'I':
            rollCam.setRandomPos(360);
            break;
        case 'O':
            rollCam.setRandomScale(1.0, 2.0);
            break;
        case 'G':
            rollCam.setPos(0, 0, 0);
            break;
        case 'H':
            rollCam.setScale(1.2);
            break;*/
        case 'P':
            agentDebug = true;
            break;
        case 'O':
            putRandumData = true;
            break;
        case 'R':
            reset();
            break;
        case 'C':
            changeColorSet();
            break;
        case 'E':
            endAnalyze = !endAnalyze;
            vPlayer.play();
            useRollCam = false;
            break;
        default:
            break;
    }
}