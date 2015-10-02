//
//  Connection.cpp
//  MauInteractive
//
//  Created by SakuragiYoshimasa on 2015/09/12.
//
//
#include "Connection.h"

void Connection::drawConnection(){
    ofFill();
    if(!connected){
        position += drawSpeed;
        if(position >= 1.0)
        {
            position = 1.0;
            connected = true;
        }else{
            ofCircle(startPoint, 40 * (1 - position));
            ofCircle(startPoint + connectionVector, 40 * position);
        }
    }
    ofSetColor(color);
    ofSetLineWidth(LINE_WIDTH);
    ofLine( startPoint, startPoint + position * (connectionVector));
    cout<<"listener started"<<endl;
}
