//
//  JsonReceiver.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/05.
//
//
#include "JsonReceiver.h"

string JsonReceiver::cachedTweetId;
ofxJSONElement JsonReceiver::jsonElement;
vector<JsonReceiver::UserInfo> JsonReceiver::usersInfo;
