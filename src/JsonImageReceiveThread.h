//
//  JsonImageReceiveThread.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/14.
//
//

#ifndef __mauInteractive__JsonImageReceiveThread__
#define __mauInteractive__JsonImageReceiveThread__

#include "ofMain.h"
#include "JsonReceiver.h"
#include "ofxThreadedImageLoader.h"

class JsonImageRecieveThread : public ofxThreadedImageLoader{
    
public:
//    static vector<ofImage> icons;
//    static vector<ofImage> get_icons();
//    
//    void threadedFunction(){
//        while (isThreadRunning()) {
//            if(lock()){
//                icons.push_back(ofImage());
//                JsonReceiver::getInstance().parseJson_icon();
//                loadFromURL(icons.back(), JsonReceiver::getInstance().recieve_icon());
//                unlock();
//                sleep(500);
//            }
//        }
//    }
};

#endif /* defined(__mauInteractive__JsonImageReceiveThread__) */
