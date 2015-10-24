//
//  ArtSpyDeforming.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/09.
//
//
#include "ArtSpyDeforming.h"

void ArtSpyDeforming::init(){
    ofxAssimpModelLoader modelLoader;
    modelLoader.loadModel("logo.stl");
    mesh = modelLoader.getMesh(0);
    light.setPointLight();
    light.setAmbientColor(ofFloatColor(0.2, 0.5, 1.0, 1.0));//環境反射光の色
    light.setDiffuseColor(ofFloatColor(0.2, 1.0, 0.2));//拡散反射光の色
    light.setSpecularColor(ofFloatColor(0, 0, 0));//鏡面反射光の色
    circuitDrawer = *new CircuitDrawer();
    circuitDrawer.init();
    foundationDrawer = *new FoundationDrawer();
    foundationDrawer.init(200);
}

void ArtSpyDeforming::update(){

    rotation +=1.4;
    if(drawCircuitMode) circuitDrawer.updateCircuite();
    foundationDrawer.update();
}

void ArtSpyDeforming::draw(){
    
    
    if(drawCircuitMode){
        ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
        circuitDrawer.drawCircuit();
        ofDisableBlendMode();
        ofDisableAlphaBlending();
    }else{
        backShader.load("","shader.frag");
        backShader.begin();
        backShader.setUniform1f("u_time", ofGetElapsedTimef());
        backShader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
        ofRect(0,0,ofGetWidth(), ofGetHeight());
        backShader.end();
        
        light.enable();
        glEnable(GL_LIGHTING);
        ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

        ofPushMatrix();
        //ofTranslate(ofGetWidth()/2, 180, -200);
        ofTranslate(ofGetWidth()/2, 280, -200);
        ofRotateZ(180);
        backShader.load("","foundation.frag");
        backShader.begin();
        backShader.setUniform1f("u_time", ofGetElapsedTimef());
        backShader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
        backShader.setUniform1f("height", 1000);
        if(apperLogo)ofDrawCone(1500, 1000);
        backShader.end();
        ofPopMatrix();
        
        //ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight() - 200,-200);
        ofRotateX(120);
        ofSetColor(40, 255, 100, 255);
        foundationDrawer.drawFoundation();
        ofPopMatrix();
        
        ofDisableBlendMode();
        ofDisableAlphaBlending();
        light.disable();
        glDisable(GL_LIGHTING);
        if(apperLogo) drawSpyLogo();
    }
    
    ofEnableAlphaBlending();
    ofDisableDepthTest();
    ofDisableBlendMode();
    ofDisableAlphaBlending();
 
}

void ArtSpyDeforming::drawSpyLogo(){
    ofPushMatrix();
    ofPushStyle();
    light.enable();
    glEnable(GL_LIGHTING);
    ofSetColor(40, 255, 100, 150);
   // ofSetColor(40, 255, 100, 255);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, -100);
    ofTranslate(0,200,0);
    ofRotateX(90);
    ofRotateZ(rotation);
    if(!drawCircuitMode){
        ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);
    }
    mesh.draw();
    light.disable();
    glDisable(GL_LIGHTING);
    if(!drawCircuitMode){
        ofDisableBlendMode();
        ofDisableAlphaBlending();
    }
    ofPopStyle();
    ofPopMatrix();
}

void ArtSpyDeforming::stop(){
    circuitDrawer.endBoxCircuit();
}

void ArtSpyDeforming::keyPressed(int key){
    switch (key) {
        case 'z':
            drawCircuitMode = !drawCircuitMode;
            circuitDrawer.endBoxCircuit();
            break;
        case 'x':
            circuitDrawer.changeMode(CircuitDrawer::NORMAL);
            break;
        case 'c':
            circuitDrawer.changeMode(CircuitDrawer::HORIZONTAL);
            break;
        case 'v':
            circuitDrawer.changeMode(CircuitDrawer::VERTICAL);
            break;
        case 'b':
            circuitDrawer.changeMode(CircuitDrawer::RIGHT_UP);
            break;
        case 'n':
            circuitDrawer.changeMode(CircuitDrawer::LEFT_UP);
            break;
        case 'm':
            circuitDrawer.changeMode(CircuitDrawer::CROSS);
            break;
        case 'a':
            circuitDrawer.initBoxCircuit();
            drawCircuitMode = true;
            break;
        case 's':
            circuitDrawer.endBoxCircuit();
            drawCircuitMode = true;
            break;
        case 'l':
            apperLogo = !apperLogo;
        default:
            break;
    }
}