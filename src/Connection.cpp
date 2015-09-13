//
//  Connection.cpp
//  MauInteractive
//
//  Created by SakuragiYoshimasa on 2015/09/12.
//
//
#include "Connection.h"

void Connection::drawConnection(){
    
    position += drawSpeed;
    if(position >= 1.0)
    {
        position = 1.0;
    }
    ofSetColor(color);
    ofLine( startPoint, startPoint + position * (connectionVector));
}
