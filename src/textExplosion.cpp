//
//  textExplosion.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#include "textExplosion.h"

void textExplosion::update(){
    waitFrame++;
    if(waitFrame < drawFrame){
        if(waitFrame % 10 == 0){
            text += "bool ofxAssimpModelLoader::loadModel(ofBuffer & buffer, bool optimize, const char * extension){\nnormalizeFactor = ofGetWidth() / 2.0 \nif(scene != NULL){clear();}\n// only ever give us triangles.\naiSetImportPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT );\naiSetImportPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, true);\n// aiProcess_FlipUVs is for VAR code. Not needed otherwise. Not sure why.\n\
                unsigned int flags = aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_Triangulate | aiProcess_FlipUVs;\n    if(optimize) flags |=  aiProcess_ImproveCacheLocality | aiProcess_OptimizeGraph |\n                    aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices |\n                    aiProcess_RemoveRedundantMaterials;\n\
                scene = shared_ptr<const aiScene>(aiImportFileFromMemory(buffer.getBinaryBuffer(), buffer.size(), flags, extension),aiReleaseImport);\n\
                if(scene){\n\
                    calculateDimensions();\n\
                    loadGLResources();\nupdate();";
        }
        if(waitFrame % 20 == 0){
            text += "\n";
        }
    }
}

void textExplosion::draw(){
    drawer.drawString(text, ofRandom(-100,ofGetWidth() + 50), ofRandom(-100,ofGetHeight() + 50));
}

void textExplosion::init(){
    ofSetColor(50,255,50);
    ofSetBackgroundAuto(false);
}

void textExplosion::end(){
    ofSetBackgroundAuto(true);
}

