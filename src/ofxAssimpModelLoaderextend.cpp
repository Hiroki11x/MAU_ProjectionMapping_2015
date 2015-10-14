//
//  ofxAssimpModelLoaderextend.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/30.
//
//
#include "ofxAssimpModelLoaderExtend.h"

void ofxAssimpModelLoaderExtend::addMesh(){
    //int i  = ofRandom(3.9);
    meshNum[0]+=100;
}

void ofxAssimpModelLoaderExtend::changeRange(){
    for(int i = 0; i < 4; i++){
       // showMeshIndex[i] = ofRandom(modelMeshNum[i]/3.0 - meshNum[i]);
    }
}

void ofxAssimpModelLoaderExtend::draw(ofPolyRenderMode renderType){
    
    //spentFrame++;
    if(spentFrame % 15 == 0){changeRange();}
    if(scene == NULL) {return;}
    
    ofPushStyle();
    
    if(!ofGetGLProgrammableRenderer()){
#ifndef TARGET_OPENGLES
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
        glPolygonMode(GL_FRONT_AND_BACK, ofGetGLPolyMode(renderType));
#endif
        glEnable(GL_NORMALIZE);
    }
    
    ofPushMatrix();
    ofMultMatrix(modelMatrix);
    
    for(unsigned int i=0; i<modelMeshes.size(); i++) {
    //for(unsigned int i=0; i<meshNum; i++) {
        ofxAssimpMeshHelper & mesh = modelMeshes[i];
        
        ofPushMatrix();
        ofMultMatrix(mesh.matrix);
        
        if(bUsingTextures){
            if(mesh.hasTexture()) {
                mesh.getTextureRef().bind();
            }
        }
        
        if(bUsingMaterials){
            mesh.material.begin();
        }
        
        if(mesh.twoSided) {
            glEnable(GL_CULL_FACE);
        }
        else {
            glDisable(GL_CULL_FACE);
        }
        
        ofEnableBlendMode(mesh.blendMode);
#ifndef TARGET_OPENGLES
        //mesh.vbo.drawElements(GL_TRIANGLES,mesh.indices.size());
        //mesh.vbo.drawElements(GL_LINES,meshNum);
        //mesh.vbo.drawElementsInstanced(GL_LINES, meshNum, ofRandom(2000));
        //mesh.vbo.draw(GL_LINES, showMeshIndex[i], meshNum[i]);
        
        //mesh.vbo.draw(GL_LINES, 0, spentFrame * 3);
        mesh.vbo.draw(GL_LINES, (mesh.indices.size() -10000) * abs(sin(float(ofGetElapsedTimeMillis())/2000.0)), 10000);
#else
        switch(renderType){
            case OF_MESH_FILL:
                mesh.vbo.drawElements(GL_TRIANGLES,mesh.indices.size());
                break;
            case OF_MESH_WIREFRAME:
                mesh.vbo.drawElements(GL_LINES,mesh.indices.size());
                
                //
                break;
            case OF_MESH_POINTS:
                mesh.vbo.drawElements(GL_POINTS,mesh.indices.size());
                break;
        }
#endif
        if(bUsingTextures){
            if(mesh.hasTexture()) {
                mesh.getTextureRef().unbind();
            }
        }
        
        if(bUsingMaterials){
            mesh.material.end();
        }
        
        ofPopMatrix();
    }
    
    ofPopMatrix();
    
    if(!ofGetGLProgrammableRenderer()){
#ifndef TARGET_OPENGLES
        glPopClientAttrib();
        glPopAttrib();
#endif
    }
}