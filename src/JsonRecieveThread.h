//
//  JsonRecieveThread.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/14.
//
//

#ifndef __mauInteractive__JsonRecieveThread__
#define __mauInteractive__JsonRecieveThread__

#include "ofMain.h"
#include "JsonReceiver.h"

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

#endif /* defined(__mauInteractive__JsonRecieveThread__) */
