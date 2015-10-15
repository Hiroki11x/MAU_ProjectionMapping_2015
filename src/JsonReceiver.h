//
//  JsonReceiver.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/07.
//
//

#ifndef __mauInteractive__JsonReceiver__
#define __mauInteractive__JsonReceiver__

#include "ofxJSON.h"
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

class JsonReceiver {
public:
    
    struct UserInfo{//Usernameと画像情報を持つ構造体
        wstring text;//つぶやいた内容(これだけ["user"]内ではない)
        string userName;
        string twitterId;//screen_name @アカウント名
        int friends_count;//フォローしてるアカウント数
        int statuses_count;//つぶやいてる数
        int followers_count;
        string iconURL;
//        ofImage iconURL;
    };
    
    vector<UserInfo> getUsersInfo();
    
    bool checkIsNewData();
    bool checkUpdateJson();
    void parseJson();
    bool recieve();
    string parseJson_icon();
    string recieve_icon();
    void init();
    UserInfo getRandomTweetInfo();
    
    int updateNum;
    bool fetchImageMode;
    bool isNewData;
    int64_t cachedTweetId;
    
    vector<UserInfo> usersInfo;
    vector<ofImage> icons;
    
    ofxJSONElement jsonElement;
    
    static wstring convToWString(string src);
    template <class T>
    static wstring convToUCS4(basic_string<T> src);
    
    static JsonReceiver &getInstance();
    
    ofxThreadedImageLoader thread;
private:
    JsonReceiver(){}
    JsonReceiver(const JsonReceiver &other){}
    JsonReceiver &operator=(const JsonReceiver &other){}
};

#endif /* defined(__mauInteractive__JsonReceiver__) */
