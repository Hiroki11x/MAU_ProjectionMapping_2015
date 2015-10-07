//
//  JsonReceiver.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/05.
//
//
#ifndef JsonReceiver_h
#define JsonReceiver_h

#include "ofxJSON.h"
#include "ofMain.h"

class JsonReceiver {
public:
    struct UserInfo{
        string userName;
        ofImage icon;
    };
    
    static int updateNum;
    static bool fetchImageMode;
    static int64_t cachedTweetId;
    static vector<UserInfo> usersInfo;
    static vector<string> userNames;
    static ofxJSONElement jsonElement;
    
    static bool checkUpdateJson();
    static void parseJson();
    static bool recieve();
    static void init();
    
private:
    JsonReceiver(){};
};
#endif