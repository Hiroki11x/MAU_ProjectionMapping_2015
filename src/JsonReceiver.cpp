//
//  JsonReceiver.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/07.
//
//

#include "JsonReceiver.h"


string JsonReceiver::cachedTweetId;
ofxJSONElement JsonReceiver::jsonElement;
vector<JsonReceiver::UserInfo> JsonReceiver::usersInfo;