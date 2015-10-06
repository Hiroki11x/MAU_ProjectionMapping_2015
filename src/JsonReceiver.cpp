//
//  JsonReceiver.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/05.
//
//
#include "JsonReceiver.h"

bool JsonReceiver::fetchImageMode = false;
string JsonReceiver::cachedTweetId;
vector<JsonReceiver::UserInfo> JsonReceiver::usersInfo;
vector<string> JsonReceiver::userNames;
ofxJSONElement JsonReceiver::jsonElement;

bool JsonReceiver::checkUpdateJson(){
    if(jsonElement["id_str"].asCString() != cachedTweetId){
        cachedTweetId = jsonElement["id_str"].asCString();
        return true;
    }else{
        return false;
    }
}

void JsonReceiver::recieve(){
    bool parsingSuccessful = jsonElement.openLocal("MAU_twit/twitter.json");
    if (parsingSuccessful){
        if(checkUpdateJson()){
            parseJson();
        }
    }else{
        cout << "Failed to parse JSON" << endl;
    }
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
}