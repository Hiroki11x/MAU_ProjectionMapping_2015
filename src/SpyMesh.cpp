//
//  SpyMesh.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#include "SpyMesh.h"

bool button = false;
ofVec3f targetVec;
ofVec3f fireVec;
UserAgent agents[4];

void SpyMesh::update(){
    
    /*agents.update();
    if(spentFrames % 10 == 0){
        agents.addConnection(ofRandom(agents.getUserAgentSize()),ofRandom(agents.getUserAgentSize()), ofRandom(50));
    }
    
    model.update();
    if(bAnimateMouse) {
        model.setPositionForAllAnimations(animationPosition);
    }
    mesh = model.getCurrentAnimatedMesh(0);
     */
    //if(spentFrames > 6558){return;}
    if(button){
        spentFrames+=1;
        
        if(spentFrames % 1 == 0){
            targetVec = modelDrawer.addVertices(spentFrames);
            if(spentFrames % 60 == 0){
                fireVec = fromVec[int(ofRandom(0,4))];
            }
        }
    }
    
    
    float * val = ofSoundGetSpectrum(1);
    modelSize = val[0] * 10;
    
    for(int i = 0; i < 4; i++){
        agents[i].update();
    }
    //camera.setPosition(400 * sin((float)ofGetElapsedTimeMillis()/1000.0), 400 * cos((float)ofGetElapsedTimeMillis()/1000.0),400 );
    camera.setPosition(329 , 131 , 132);
    camera.lookAt(ofPoint(ofGetWidth()/2, ofGetHeight()/2,0));
    //cout << "x:" << camera.getPosition().x << endl;
    //cout << "y:" << camera.getPosition().y << endl;
    //cout << "z:" << camera.getPosition().z << endl;
}

void SpyMesh::draw(){
    
    camera.begin();
    

    ofDrawSphere(0,0,0, 1);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    //ofRotateX(spentFrames);
    if(button){
        ofSetLineWidth(0.3);
        ofSetColor(50, 255, 50 , 150);
       // ofLine(fireVec, fireVec + ( targetVec - fireVec) * float(spentFrames % 5) /5.0 );
        
        
        
        
        ofRotateX(ofGetElapsedTimef() * 10);
        ofRotateY(ofGetElapsedTimef() * 10);
        ofRotateZ(ofGetElapsedTimef() * 10);
        modelDrawer.drawModel(modelSize);
        ofLine(fireVec, targetVec );
        ofDrawSphere(fireVec, (60.0 - float(spentFrames % 60)) * 0.8 + 10);
        ofDrawBitmapString(ofToString(spentFrames) + " FPS:"+ofToString(ofGetFrameRate()) ,fireVec);
        for(int i = 0; i < 8; i++){
            
            ofPushMatrix();
            ofRotateX(ofGetElapsedTimef() * i * 20);
            ofRotateY(ofGetElapsedTimef() * i * 20);
            ofRotateZ(ofGetElapsedTimef() * i * 20);
         //   agents[i].draw();
          ofDrawSphere(fromVec[i % 4], (60.0 - float(spentFrames % 60)) * 0.5);
            
            ofPopMatrix();
        }
        
    }
    

    
    //for(int i = 0; i < 7; i++){
   // int i = 2;
        
        //ofPath line = ofPath();
        //line.setStrokeColor(ofColor(50, 50, 255));
        //line.setFilled(false);
        //line.moveTo(0,0,0);
        //ofSetColor(255 * ( (float)i / 7), 255 * (1 - (float)i / 7), 0);
    
        //for(int j = 0; j < vertx[i].size() -1; j++){
        /*for(int j = 0; j < spentFrames; j++){
            
            line.lineTo(vertx[i].at(j).x * 10, vertx[i].at(j).y * 10 ,vertx[i].at(j).z * 10);
            ofLine(vertx[i].at(j).x * modelSize, vertx[i].at(j).y * modelSize ,vertx[i].at(j).z * modelSize,
                   vertx[i].at(j + 1).x * modelSize, vertx[i].at(j + 1).y * modelSize ,vertx[i].at(j + 1).z * modelSize);
            //ofDrawSphere(vertx[i].at(j),10);
            //ofVertex(vertx[i].at(j));
            //cout << vertx[i].at(j).x << endl;
        }*///
    
        //line.draw();
        //line.close();
   // }
   
    
    ofPopMatrix();
    ofSetColor(255);
    
    
   /* agents.draw();
    
    ofPushStyle();

    ofSetColor(255);
    ofSetLineWidth(2);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    glShadeModel(GL_SMOOTH); //some model / light stuff
    light.enable();
    ofEnableSeparateSpecularLight();
    
    ofPushMatrix();
    
    ofTranslate(model.getPosition().x+100, model.getPosition().y, 0);
    ofRotate(-spentFrames, 0, 1, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 50 * sin(ofGetElapsedTimeMillis()/240.0));
    model.drawWireframe();
    
    ofPopMatrix();
    
    if(ofGetGLProgrammableRenderer()){
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
    }
    glEnable(GL_NORMALIZE);
    
    ofPushMatrix();
    
    ofTranslate(model.getPosition().x-300, model.getPosition().y, 0);
    ofRotate(-mouseX, 0, 1, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
    
    ofxAssimpMeshHelper & meshHelper = model.getMeshHelper(0);
    
    ofMultMatrix(model.getModelMatrix());
    ofMultMatrix(meshHelper.matrix);
    
    ofMaterial & material = meshHelper.material;
    if(meshHelper.hasTexture()){
        meshHelper.getTextureRef().bind();
    }
    material.begin();
    //mesh.drawWireframe();
    material.end();
    if(meshHelper.hasTexture()){
        meshHelper.getTextureRef().unbind();
    }
    
    ofPopMatrix();
    
    if(ofGetGLProgrammableRenderer()){
        glPopAttrib();
    }
    
    ofDisableDepthTest();
    light.disable();
    ofDisableLighting();
    ofDisableSeparateSpecularLight();
    
    ofSetColor(255, 255, 255 );
    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 15);
    ofSetColor(50, 255, 50);
    
    ofPopStyle();*/
    

    camera.end();
}

void SpyMesh::end(){}

void SpyMesh::init(){
    ofBackground(0);
    soundPlayer.loadSound("star.mp3");
    soundPlayer.play();
    model.loadModel("head/TheRock2.obj");
    model.setPosition(ofGetWidth()/2, (float)ofGetHeight() * 0.5 , 0);
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.
    
    bAnimate = false;
    bAnimateMouse = false;
    animationPosition = 0;
    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.playAllAnimations();
    if(!bAnimate) {
        model.setPausedForAllAnimations(true);
    }
    text = loadText("code.txt");
    spentFrames = 0;
    
   /* vector<ofMeshFace> faces;
    vector<ofMeshFace> allFaces[7];*/
    
    for(int i = 0; i < model.getMeshCount(); i++){
        
        modelDrawer.setVerices(model.getMesh(i).vertices);
        
        
        //meshes.push_back(model.getMesh(i));
        //cout << i << endl;
   //     allFaces[i] = model.getMesh(i).faces;
   //     vertx[i] = model.getMesh(i).vertices;
   //     cout << allFaces[i].size() << endl;
   //     vertexAmount[i].push_back(vertx[i].size());
        //connection[i].push_back(new vector<int>(vertx[i].size()));
    }
    button = false;
    for(int i = 0; i < 4; i++){
        agents[i] = *new UserAgent();
        agents[i].set_position(ofVec2f(fromVec[i].x,fromVec[i].y));
        
    }
  
    camera.lookAt(ofPoint(0,0,0));
  
}

void SpyMesh::onMouseDown(int x, int y){
    mouseX = x;
    mouseY = y;
    //model.addMesh();
    //agents.addAgent(ofVec2f(x, y));
    button = true;
}