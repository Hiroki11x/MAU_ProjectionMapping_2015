//
//  JsonRecieveThread.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/10.
//
//
#ifndef JsonRecieveThread_h
#define JsonRecieveThread_h

#include "ofMain.h"
#include "JsonReceiver.h"

class JsonRecieveThread : public ofThread {
public:
    void threadedFunction(){
        while (isThreadRunning()) {
            JsonReceiver::recieve();
        }
    }
};

#endif