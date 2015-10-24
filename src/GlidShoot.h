//
//  GlidShoot.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/19.
//
//

#ifndef GlidShoot_h
#define GlidShoot_h

#include "ofMain.h"
#include "SceneElement.h"

#define SIDE_MARGIN 32
#define TOP_MARGIN 24
#define GRID_SIZE 95
#define H_GRID 14
#define V_GRID 10
#define MAX_DRAW_FRAME 15

class GlidShoot : public SceneElement {
public:
    virtual void draw() override;
    virtual void init() override;
    virtual void update() override;
    virtual void onMouseDown(int x,int y) override;
    virtual void keyPressed(int key) override;
    virtual void stop() override;
    
    typedef struct {
        int restDrawFrames;
        int drawFrames;
        bool drawGlid;
        ofColor c;
    } Glid;
    
    vector<Glid> glids;
    
    int spentFrames;
    
   // int keys[14] = {'q','w','e','r','t','y','u','i','o','p','@','[','a','s'};

};
#endif
