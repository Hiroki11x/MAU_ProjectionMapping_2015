//
//  connection.h
//  MauInteractive
//
//  Created by SakuragiYoshimasa on 2015/09/12.
//
//

#ifndef MauInteractive_Connection_h
#define MauInteractive_Connection_h

#include "ofMain.h"

class Connection {
private:
    ofVec2f startPoint;
    ofVec2f connectionVector;//方向ベクトル
    ofColor color;
    float drawSpeed;
    float position;
    
public:
    Connection(ofVec2f startPoint, ofVec2f endPoint, ofColor c, float duration = 5.0){
        this->startPoint = startPoint;
        this->connectionVector = endPoint - startPoint;
        //this->color = c;
        this->color = ofColor(0, 255, 0,100);
        this->position = 0.0;
        if(duration >= 5.0)
        {
            this->drawSpeed = 1.0 / duration;
        }else
        {
            this->drawSpeed = 0.2;
        }
    };
    
    void drawConnection();
};
#endif