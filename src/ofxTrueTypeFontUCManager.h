//
//  ofxTrueTypeFontUCManager.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/10.
//
//

#ifndef __mauInteractive__ofxTrueTypeFontUCManager__
#define __mauInteractive__ofxTrueTypeFontUCManager__

#include "ofMain.h"
//#include "ofxTrueTypeFontUC.h"

class ofxTrueTypeFontUCManager{

public:
    
    ofxTrueTypeFontUCManager();
//    void drawString(string arg,float x,float y);
    void drawString(const string &str, float x, float y);
    
//    void loadFont(string name, int size);
    bool loadFont(string filename, int fontsize, bool bAntiAliased=true, bool makeContours=false, float simplifyAmt=0.3, int dpi=0);
    
private:
//    ofxTrueTypeFontUC font;
    class Impl;
    Impl *mImpl;
    
};

#endif /* defined(__mauInteractive__ofxTrueTypeFontUCManager__) */
