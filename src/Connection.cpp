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
        }else if (position <= 0.2){
            ofCircle(startPoint, 40 * (1 - position));
        }else if (position >= 0.8){
            ofCircle(startPoint + connectionVector, 40 * position);
        }
    }
    ofSetColor(color);
    ofLine( startPoint, startPoint + position * (connectionVector));
}
