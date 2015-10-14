//
//  JsonReceiver.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/07.
//
//

#include "JsonReceiver.h"

JsonReceiver &JsonReceiver::getInstance() {
    static JsonReceiver instance;
    return instance;
}

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

vector<wstring> JsonReceiver::getUserNames(){
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
    bool parsingSuccessful = jsonElement.openLocal("../../../MAU_twit/twitter.json");
    if (parsingSuccessful){
        if(checkUpdateJson()){
            parseJson();
            return true;
        }
    }else{
        cout << "Failed to parse JSON" << endl;
    }
    return false;
}

void JsonReceiver::parseJson(){
    
    usersInfo.push_back((UserInfo){
        convToWString(jsonElement["text"].asCString()),
        jsonElement["user"]["name"].asCString(),
        jsonElement["user"]["screen_name"].asCString(),
        jsonElement["user"]["friends_count"].asInt(),
        jsonElement["user"]["statuses_count"].asInt(),
        jsonElement["user"]["followers_count"].asInt(),
        jsonElement["user"]["profile_image_url"].asCString()});
    userNames.push_back(convToWString(jsonElement["user"]["name"].asCString()));
    updateNum++;
    isNewData = true;
    return;
}

void JsonReceiver::init(){
    bool parsingSuccessful = jsonElement.openLocal("../../../MAU_twit/twitter.json");
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


wstring JsonReceiver::convToWString(string src) {
    
#ifdef TARGET_WIN32
    wstring dst = L"";
    typedef codecvt<wchar_t, char, mbstate_t> codecvt_t;
    
    locale loc = locale("");
    if(!std::has_facet<codecvt_t>(loc))
        return dst;
    
    const codecvt_t & conv = use_facet<codecvt_t>(loc);
    
    const std::size_t size = src.length();
    std::vector<wchar_t> dst_vctr(size);
    
    if (dst_vctr.size() == 0)
        return dst;
    
    wchar_t * const buf = &dst_vctr[0];
    
    const char * dummy;
    wchar_t * next;
    mbstate_t state = {0};
    const char * const s = src.c_str();
    
    if (conv.in(state, s, s + size, dummy, buf, buf + size, next) == codecvt_t::ok)
        dst = std::wstring(buf, next - buf);
    
    return dst;
#elif defined __clang__
    wstring dst = L"";
    for (int i=0; i<src.size(); ++i)
        dst += src[i];
#if defined(__clang_major__) && (__clang_major__ >= 4)
    dst = convToUCS4<wchar_t>(dst);
#endif
    return dst;
#else
    return convToUCS4<char>(src);
#endif
}

template <class T>
wstring JsonReceiver::convToUCS4(basic_string<T> src) {
    wstring dst = L"";
    // convert UTF-8 on char or wchar_t to UCS-4 on wchar_t
    int size = src.size();
    int index = 0;
    while (index < size) {
        wchar_t c = (unsigned char)src[index];
        if (c < 0x80) {
            dst += (c);
        }else if (c < 0xe0) {
            if (index + 1 < size) {
                dst += (((c & 0x1f) << 6) | (src[index+1] & 0x3f));
                index++;
            }
        }else if (c < 0xf0) {
            if (index + 2 < size) {
                dst += (((c & 0x0f) << 12) | ((src[index+1] & 0x3f) << 6) |
                        (src[index+2] & 0x3f));
                index += 2;
            }
        }else if (c < 0xf8) {
            if (index + 3 < size) {
                dst += (((c & 0x07) << 18) | ((src[index+1] & 0x3f) << 12) |
                        ((src[index+2] & 0x3f) << 6) | (src[index+3] & 0x3f));
                index += 3;
            }
        }else if (c < 0xfc) {
            if (index + 4 < size) {
                dst += (((c & 0x03) << 24) | ((src[index+1] & 0x3f) << 18) |
                        ((src[index+2] & 0x3f) << 12) | ((src[index+3] & 0x3f) << 6) |
                        (src[index+4] & 0x3f));
                index += 4;
            }
        }else if (c < 0xfe) {
            if (index + 5 < size) {
                dst += (((c & 0x01) << 30) | ((src[index+1] & 0x3f) << 24) |
                        ((src[index+2] & 0x3f) << 18) | ((src[index+3] & 0x3f) << 12) |
                        ((src[index+4] & 0x3f) << 6) | (src[index+5] & 0x3f));
                index += 5;
            }
        }
        index++;
    }
    return dst;
}