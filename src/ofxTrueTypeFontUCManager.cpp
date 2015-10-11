//
//  ofxTrueTypeFontUCManager.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/10.
//
//

#include "ofxTrueTypeFontUCManager.h"

//
//void ofxTrueTypeFontUCManager::drawString(string arg,float x,float y){
//    font.drawString(arg, x, y);
//}
//void ofxTrueTypeFontUCManager::loadFont(string name, int size){
//    font.loadFont(name, size);
//}


typedef struct {
    int character;
    int height;
    int width;
    int setWidth;
    int topExtent;
    int leftExtent;
    float tW,tH;
    float x1,x2,y1,y2;
    float t1,t2,v1,v2;
} charPropsUC;

class ofxTrueTypeFontUCManager::Impl {
public:
    Impl() :librariesInitialized_(false){};
    ~Impl() {};
    
    bool implLoadFont(string filename, int fontsize, bool _bAntiAliased, bool makeContours, float _simplifyAmt, int dpi);
    void implReserveCharacters(int num);
    void implUnloadFont();
    
    bool bLoadedOk_;
    bool bAntiAliased_;
    int limitCharactersNum_;
    float simplifyAmt_;
    int dpi_;
    
    vector <ofPath> charOutlines;
    
    float lineHeight_;
    float letterSpacing_;
    float	spaceSize_;
    
    vector<charPropsUC> cps;  // properties for each character
    
    int	fontSize_;
    bool bMakeContours_;
    
    void drawChar(int c, float x, float y);
    void drawCharAsShape(int c, float x, float y);
    
    int	border_;  // visibleBorder;
    string filename_;
    
    // ofTexture texAtlas;
    vector<ofTexture> textures;
    bool binded_;
    ofMesh stringQuads;
    
    typedef struct FT_LibraryRec_ * FT_Library;
    typedef struct FT_FaceRec_ * FT_Face;
    FT_Library library_;
    FT_Face face_;
    bool librariesInitialized_;
    
    bool loadFontFace(string fontname);
    
    ofPath getCharacterAsPointsFromCharID(const int & charID);
    
    void bind(const int & charID);
    void unbind(const int & charID);
    
    int getCharID(const int & c);
    void loadChar(const int & charID);
    vector<int> loadedChars;
    
    static const int kTypefaceUnloaded;
    static const int kDefaultLimitCharactersNum;
    
    void unloadTextures();
    bool initLibraries();
    void finishLibraries();
    
#ifdef TARGET_OPENGLES
    GLint blend_src, blend_dst_;
    GLboolean blend_enabled_;
    GLboolean texture_2d_enabled_;
#endif
};

#ifdef TARGET_WIN32

static const basic_string<unsigned int> convToUTF32(const string &src) {
    if (src.size() == 0) {
        return basic_string<unsigned int> ();
    }
    
    // convert XXX -> UTF-16
    const int n_size = ::MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, NULL, 0);
    vector<wchar_t> buffUTF16(n_size);
    ::MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, &buffUTF16[0], n_size);
    
    // convert UTF-16 -> UTF-8
    const int utf8str_size = ::WideCharToMultiByte(CP_UTF8, 0, &buffUTF16[0], -1, NULL, 0, NULL, 0);
    vector<char> buffUTF8(utf8str_size);
    ::WideCharToMultiByte(CP_UTF8, 0, &buffUTF16[0], -1, &buffUTF8[0], utf8str_size, NULL, 0);
    
    // convert UTF-8 -> UTF-32 (UCS-4)
    std::wstring_convert<std::codecvt_utf8<unsigned int>, unsigned int> convert32;
    return convert32.from_bytes(&buffUTF8[0]);
}

#else

static const basic_string<unsigned int> convToUTF32(const string &utf8_src){
    basic_string<unsigned int> dst;
    
    // convert UTF-8 -> UTF-32 (UCS-4)
    int size = utf8_src.size();
    int index = 0;
    while (index < size) {
        wchar_t c = (unsigned char)utf8_src[index];
        if (c < 0x80) {
            dst += (c);
        }
        else if (c < 0xe0) {
            if (index + 1 < size) {
                dst += (((c & 0x1f) << 6) | (utf8_src[index+1] & 0x3f));
                index++;
            }
        }
        else if (c < 0xf0) {
            if (index + 2 < size) {
                dst += (((c & 0x0f) << 12) | ((utf8_src[index+1] & 0x3f) << 6) |
                        (utf8_src[index+2] & 0x3f));
                index += 2;
            }
        }
        else if (c < 0xf8) {
            if (index + 3 < size) {
                dst += (((c & 0x07) << 18) | ((utf8_src[index+1] & 0x3f) << 12) |
                        ((utf8_src[index+2] & 0x3f) << 6) | (utf8_src[index+3] & 0x3f));
                index += 3;
            }
        }
        else if (c < 0xfc) {
            if (index + 4 < size) {
                dst += (((c & 0x03) << 24) | ((utf8_src[index+1] & 0x3f) << 18) |
                        ((utf8_src[index+2] & 0x3f) << 12) | ((utf8_src[index+3] & 0x3f) << 6) |
                        (utf8_src[index+4] & 0x3f));
                index += 4;
            }
        }
        else if (c < 0xfe) {
            if (index + 5 < size) {
                dst += (((c & 0x01) << 30) | ((utf8_src[index+1] & 0x3f) << 24) |
                        ((utf8_src[index+2] & 0x3f) << 18) | ((utf8_src[index+3] & 0x3f) << 12) |
                        ((utf8_src[index+4] & 0x3f) << 6) | (utf8_src[index+5] & 0x3f));
                index += 5;
            }
        }
        index++;
    }
    
    return dst;
}

#endif

ofxTrueTypeFontUCManager::ofxTrueTypeFontUCManager() {
    mImpl = new Impl();
    mImpl->bLoadedOk_	= false;
    mImpl->bMakeContours_	= false;
#if defined(TARGET_ANDROID) || defined(TARGET_OF_IOS)
    all_fonts().insert(this);
#endif
    mImpl->letterSpacing_ = 1;
    mImpl->spaceSize_ = 1;
    
    // 3 pixel border around the glyph
    // We show 2 pixels of this, so that blending looks good.
    // 1 pixels is hidden because we don't want to see the real edge of the texture
    mImpl->border_ = 3;
    
    mImpl->stringQuads.setMode(OF_PRIMITIVE_TRIANGLES);
    mImpl->binded_ = false;
    
    mImpl->limitCharactersNum_ = mImpl->kDefaultLimitCharactersNum;
}

//-----------------------------------------------------------
bool ofxTrueTypeFontUCManager::loadFont(string filename, int fontsize, bool bAntiAliased, bool makeContours, float simplifyAmt, int dpi) {
    return mImpl->implLoadFont(filename, fontsize, bAntiAliased, makeContours, simplifyAmt, dpi);
    
}

void ofxTrueTypeFontUCManager::drawString(const string &src, float x, float y){
    if (!mImpl->bLoadedOk_) {
        ofLog(OF_LOG_ERROR,"ofxTrueTypeFontUC::drawString - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
        return;
    }
    
    GLint index	= 0;
    GLfloat X = x;
    GLfloat Y = y;
    
    basic_string<unsigned int> utf32_src = convToUTF32(src);
    int len = (int)utf32_src.length();
    int c, cy;
    
    while (index < len) {
        c = utf32_src[index];
        if (c == '\n') {
            Y += mImpl->lineHeight_;
            X = x ; //reset X Pos back to zero
        }
        else if (c == ' ') {
            int cy = mImpl->getCharID('p');
            X += mImpl->cps[cy].width * mImpl->letterSpacing_ * mImpl->spaceSize_;
        }
        else {
            cy = mImpl->getCharID(c);
            if (mImpl->cps[cy].character == mImpl->kTypefaceUnloaded)
                mImpl->loadChar(cy);
            mImpl->bind(cy);
            mImpl->drawChar(cy, X, Y);
            mImpl->unbind(cy);
            X += mImpl->cps[cy].setWidth * mImpl->letterSpacing_;
        }
        index++;
    }
}


