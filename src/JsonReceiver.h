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
    
    static string cachedTweetId;
    
    static ofxJSONElement jsonElement;
    static vector<UserInfo> usersInfo;
    
    static void recieve(){
        
        bool parsingSuccessful = jsonElement.openLocal("MAU_twit/twitter.json");
        
        if (parsingSuccessful){
            //cout << jsonElement.getRawString(true) << endl;
            if(checkUpdateJson()){
                parseJson();
            }
        }else{
            cout << "Failed to parse JSON" << endl;
        }
    };
    static void parseJson(){
        ofImage img;
        img.loadImage(jsonElement["user"]["profile_image_url"].asCString());
        if(img.getWidth() == 0){return;}
        usersInfo.push_back((UserInfo){jsonElement["user"]["name"].asCString(),img});
    };
    static bool checkUpdateJson(){
        if(jsonElement["id_str"].asCString() != cachedTweetId){
            cachedTweetId = jsonElement["id_str"].asCString();
            return true;
        }else{
            return false;
        }
    };
    
private:
    JsonReceiver(){};
};
#endif 
