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
    graphDrawer.updateGraphParams();
    markerDrawer.update();
    if(JsonReceiver::getInstance().checkIsNewData()){
        agents.push_back(*new AgentAnalysis(lineEmitPoints[int(ofRandom(6))], JsonReceiver::getInstance().getUserNames().at(JsonReceiver::getInstance().updateNum - 1)));
        agentDebug = false;
        agentNum++;
        cout << agentNum << "agetn" << endl;
    }
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
    }else{
        camera.setPosition(ofPoint(ofGetWidth()/2 + 300 * sin(float(ofGetElapsedTimef())/3.0) , ofGetHeight()/2 + 300 * cos(float(ofGetElapsedTimef())/3.0) , 150 + 250 * cos(float(ofGetElapsedTimef() / 10.0))));
        camera.lookAt(ofPoint(ofGetWidth()/2, ofGetHeight()/2,0));

        light.setPosition(ofPoint(ofGetWidth()/2 + 300 * sin(float(ofGetElapsedTimef())/3.0) , ofGetHeight()/2 + 300 * cos(float(ofGetElapsedTimef())/3.0) , 150 + 250 * cos(float(ofGetElapsedTimef() / 10.0))));
        light.lookAt(ofPoint(ofGetWidth()/2, ofGetHeight()/2,0));
    }
}

void SpyMesh::updateVertices(){
    
    for(int n = 0; n < agents.size(); n++){
        for(float f = 0; f < 1; f+=ADD_TRIANGLE_PER_AGENT_TRIANGLE){
            agents.at(n).removeVertices();
        }
        if(agents.at(n).removeVertices()){
            agents.at(n).targetPodsition = modelDrawer.addVertex();
            cout << "addVertex" << endl;
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
    graphDrawer.drawGraphGui();
    markerDrawer.drawTargetMarker();
    backShader.load("","shader.frag");
    backShader.begin();
    backShader.setUniform1f("u_time", ofGetElapsedTimef());
    backShader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    ofRect(0,0,ofGetWidth(), ofGetHeight());
    backShader.end();
   
    ofPushMatrix();
    ofPushStyle();
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    if(useRollCam){
        rollCam.begin();
    }else{
        camera.begin();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    }
    
    ofSetColor(50, 255, 50 , 150);
    
    
    ofSetLineWidth(0.3);
    if(modelDrawMode) {
        modelDrawer.drawModel(modelSize);
        drawEmitter();
    }
    if(coloerMeshDrawMode) modelDrawer.drawColoredMesh();
    if(randomTrianlgeDrawMode) {
        rtDrawer.drawTriangleMesh();
        spiralDrawer.drawSpiral(modelSize);
    }
    if(garallyDrawMode) garallyDrawer.drawGarally();
    if(randomExpandMeshDrawMode) modelDrawer.drawRandomExpandMesh(modelSize);
    

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
    ofDrawBitmapString(ofToString(spentFrames) + " FPS:"+ofToString(ofGetFrameRate()) ,0,0);
    
}

void SpyMesh::drawEmitter(){

    ofPushStyle();
    ofSetColor(50, 255, 50,150);
    
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
    markerDrawer.init(60);
    graphDrawer = *new GraphGuiDrawer(ofVec2f(300,100));
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

void SpyMesh::onMouseDown(int x, int y){
    mouseX = x;
    mouseY = y;
}

void SpyMesh::reset(){
    modelDrawer.reset();
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
        //CamSettings
        case 'y':
            useRollCam = !useRollCam;
            break;
        case 'u':
            rollCam.setRandomScale(1.5, 2.0);
            rollCam.setRandomPos(360);
            break;
        case 'i':
            rollCam.setRandomPos(360);
            break;
        case 'o':
            rollCam.setRandomScale(1.5, 2.0);
            break;
        case 'g':
            rollCam.setPos(0, 0, 0);
            break;
        case 'h':
            rollCam.setScale(1.2);
            break;
        case 'p':
            agentDebug = true;
            break;
        case 'R':
            reset();
        default:
            break;
    }
}