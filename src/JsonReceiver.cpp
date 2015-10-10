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
bool JsonReceiver::isNewData = false;
int64_t JsonReceiver::cachedTweetId;
vector<JsonReceiver::UserInfo> JsonReceiver::usersInfo;
vector<string> JsonReceiver::userNames;
ofxJSONElement JsonReceiver::jsonElement;

bool JsonReceiver::checkIsNewData(){

    if(isNewData){
        isNewData = false;
        return true;
    }
    return false;
}

vector<JsonReceiver::UserInfo> JsonReceiver::getUsersInfo(){
    return usersInfo;
}

vector<string> JsonReceiver::getUserNames(){
    return  userNames;
}

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
            isNewData = true;
            return true;
        }
    }else{
        cout << "Failed to parse JSON" << endl;
    }
    return false;
}

void JsonReceiver::parseJson(){
    
    ofImage img;
    if(fetchImageMode){
        img.loadImage(jsonElement["user"]["profile_image_url"].asCString());
        if(img.getWidth() == 0){return;}
    }
    usersInfo.push_back((UserInfo){jsonElement["user"]["name"].asCString(),img, jsonElement["text"].asCString()});
    //usersInfo.push_back((UserInfo){"ds",img, jsonElement["text"].asCString()});
    //usersInfo.push_back((UserInfo){"asdfg",img, "sdfg"});
    userNames.push_back(jsonElement["user"]["name"].asCString());
    //userNames.push_back("asdfghjk");
    
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

JsonReceiver::UserInfo JsonReceiver::getRandomTweetInfo(){
    
    return getUsersInfo().at(ofRandom(0, usersInfo.size() - 0.1));
}