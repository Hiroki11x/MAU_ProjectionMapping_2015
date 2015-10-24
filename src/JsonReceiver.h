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
    
    
    //-----------------------------------
    //No tweet用
    //-----------------------------------
    vector<wstring> dammyNameData;
    vector<wstring> getDammyTextData();
    vector<wstring> dammyTextData;
    vector<wstring> getDammyUserNameData();
    vector<ofImage> dammyImageData;
    vector<ofImage> getDammyImageData();
    void initDammyData();
private:
    JsonReceiver(){}
    JsonReceiver(const JsonReceiver &other){}
    JsonReceiver &operator=(const JsonReceiver &other){}
};
#endif