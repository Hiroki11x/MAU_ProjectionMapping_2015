//
//  SpiralDrawer.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/08.
//
//
#include "SpiralDrawer.h"

void SpiralDrawer::init(float scale){
    /*for(int i = RECT_LENGTH; i > 0; i--){
        spiralMesh.addVertex(ofVec3f(RECT_WIDTH,RECT_HEIGHT, - i * INTERVAL ));
        spiralMesh.addVertex(ofVec3f(RECT_WIDTH,-RECT_HEIGHT, - i * INTERVAL ));
        spiralMesh.addVertex(ofVec3f(RECT_WIDTH,-RECT_HEIGHT, - i * INTERVAL ));
        spiralMesh.addVertex(ofVec3f(-RECT_WIDTH,-RECT_HEIGHT, - i * INTERVAL ));
        spiralMesh.addVertex(ofVec3f(-RECT_WIDTH,-RECT_HEIGHT, - i * INTERVAL ));
        spiralMesh.addVertex(ofVec3f(-RECT_WIDTH,RECT_HEIGHT, - i * INTERVAL ));
        spiralMesh.addVertex(ofVec3f(-RECT_WIDTH,RECT_HEIGHT, - i * INTERVAL ));
        spiralMesh.addVertex(ofVec3f(RECT_WIDTH,RECT_HEIGHT, - i * INTERVAL ));
    }*/
    scale = 1;
    spiralMesh.clear();
    model.loadModel("Spiral/s5.stl");
    model.setScale(scale, scale, scale);
   // for(int i = 0; i < model.getMeshCount(); i++){
       /* spiralMesh.vertices.insert(spiralMesh.vertices.end(), model.getMesh(i).vertices.begin(), model.getMesh(i).vertices.end());*/
    /*    spiralMesh.addVertices(model.getMesh(i).vertices);
        cout << spiralMesh.vertices.size() << endl;
    }
    spiralVbo.setMesh(spiralMesh, 1000);
    modelMatrix.glScale(scale, scale, scale);*/

}

void SpiralDrawer::drawSpiral(float t){
    model.spentFrame = t * 100;
    model.draw(ofPolyRenderMode::OF_MESH_WIREFRAME);
    
   //spiralMesh.draw();
    if(float(spiralMesh.vertices.size()) * t < 1){
        return;
    }
    //spiralVbo.draw(GL_TRIANGLES, 0, int(float(spiralMesh.vertices.size()) * t));
    //spiralVbo.draw(20, 1, (int)t);
}