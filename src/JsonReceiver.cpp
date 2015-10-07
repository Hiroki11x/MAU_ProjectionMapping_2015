//
//  JsonReceiver.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/05.
//
//
#include "JsonReceiver.h"

int JsonReceiver::updateNum = 0;
bool JsonReceiver::fetchImageMode = false;
int64_t JsonReceiver::cachedTweetId;
vector<JsonReceiver::UserInfo> JsonReceiver::usersInfo;
vector<string> JsonReceiver::userNames;
ofxJSONElement JsonReceiver::jsonElement;

bool JsonReceiver::checkUpdateJson(){
    
    if(jsonElement["id"].asInt64() != cachedTweetId){
        cachedTweetId = jsonElement["id"].asInt64();
        return true;
    }else{
        return false;
    }
}

bool JsonReceiver::recieve(){
    bool parsingSuccessful = jsonElement.openLocal("MAU_twit/twitter.json");
    if (parsingSuccessful){
        if(checkUpdateJson()){
            parseJson();
            updateNum++;
            return true;
        }
    }else{
        cout << "Failed to parse JSON" << endl;
    }
    return false;
}

void JsonReceiver::parseJson(){
    if(fetchImageMode){
        ofImage img;
        img.loadImage(jsonElement["user"]["profile_image_url"].asCString());
        if(img.getWidth() == 0){return;}
        usersInfo.push_back((UserInfo){jsonElement["user"]["name"].asCString(),img});
    }else{
        userNames.push_back(jsonElement["user"]["name"].asCString());
    }
    return;
}

void JsonReceiver::init(){
    bool parsingSuccessful = jsonElement.openLocal("MAU_twit/twitter.json");
    if (parsingSuccessful){
        cachedTweetId = jsonElement["id"].asInt64();
    }else{
        cout << "Failed to parse JSON" << endl;
    }
    updateNum = 0;
}