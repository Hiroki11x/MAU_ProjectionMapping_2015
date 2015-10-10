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
        string text;
    };
    
    static vector<UserInfo> getUsersInfo();
    static vector<string> getUserNames();
    static bool checkIsNewData();
    static bool checkUpdateJson();
    static void parseJson();
    static bool recieve();
    static void init();
    static UserInfo getRandomTweetInfo();
    
private:
    static int updateNum;
    static bool fetchImageMode;
    static bool isNewData;
    static int64_t cachedTweetId;
    static vector<UserInfo> usersInfo;
    static vector<string> userNames;
    static ofxJSONElement jsonElement;
    JsonReceiver(){};
};

#endif