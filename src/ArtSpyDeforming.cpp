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
    //cout << mesh.vertices.size() << endl;
  //  ffd.setup(1, 2, 1);
  //  for ( int i=0; i<3; i++ ) rotates.push_back(0);
}

void ArtSpyDeforming::update(){
   /* for ( int i=0; i<3; i++ ) {
        rotates[i] += (i+1)*0.01;
        for ( int j=0; j<4; j++ ) {
            int jj = j;
            if ( jj > 1 ) jj = 5 - jj;
            ffd.setControlPointPosition(j%2, i, int(j/2)%2, ofVec3f(cos(jj*(TWO_PI/4.0)+rotates[i])*141.42135623731, i*100 - 100, sin(jj*(TWO_PI/4.0)+rotates[i])*141.42135623731));
        }
    }*/
}

void ArtSpyDeforming::draw(){
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(100, 255, 100);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, -200);
    ofTranslate(0,350,0);
    ofRotateX(90);
   // ffd.deformMesh(mesh).drawWireframe();
   // ffd.debugDraw();
    mesh.draw();
    ofPopStyle();
    ofPopMatrix();
}