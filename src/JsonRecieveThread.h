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
#include <sstream>

class JsonRecieveThread : public ofThread {
public:
    void threadedFunction(){
        
        while (isThreadRunning()) {
            if(lock()){
                JsonReceiver::getInstance().recieve();
                unlock();
                sleep(500);
            }
        }
    }
};

#endif