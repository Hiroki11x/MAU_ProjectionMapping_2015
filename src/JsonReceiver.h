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
        string iconURL;
        wstring text;
    };
    
    /*static vector<UserInfo> getUsersInfo();
     static vector<wstring> getUserNames();
     static bool checkIsNewData();
     static bool checkUpdateJson();
     static void parseJson();
     static bool recieve();
     static void init();
     static UserInfo getRandomTweetInfo();
     
     static int updateNum;
     static bool fetchImageMode;
     static bool isNewData;
     static int64_t cachedTweetId;
     static vector<UserInfo> usersInfo;
     static vector<wstring> userNames;
     static ofxJSONElement jsonElement;*/
    //JsonReceiver(){};
    
    vector<UserInfo> getUsersInfo();
    vector<wstring> getUserNames();
    bool checkIsNewData();
    bool checkUpdateJson();
    void parseJson();
    bool recieve();
    void init();
    UserInfo getRandomTweetInfo();
    
    int updateNum;
    bool fetchImageMode;
    bool isNewData;
    int64_t cachedTweetId;
    vector<UserInfo> usersInfo;
    vector<wstring> userNames;
    ofxJSONElement jsonElement;
    
    static wstring convToWString(string src);
    template <class T>
    static wstring convToUCS4(basic_string<T> src);
    

    static JsonReceiver &getInstance();
private:
    JsonReceiver(){}
    JsonReceiver(const JsonReceiver &other){}
    JsonReceiver &operator=(const JsonReceiver &other){}
};
#endif