//
//  FontManager.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/10.
//
//

#ifndef __mauInteractive__FontManager__
#define __mauInteractive__FontManager__

#include "ofMain.h"
#include "ofxTrueTypeFontUL2.h"

class FontManager{
public:
    
    FontManager(){};
    
    static ofxTrueTypeFontUL2 mfont;
    static ofxTrueTypeFontUL2 msmallfont;
    
    void loadFont(string arg, int size);
    void drawString(string arg ,float x, float y);
    
    void loadSmallFont(string arg, int size);
    void drawSmallString(string arg ,float x, float y);
};

#endif /* defined(__mauInteractive__FontManager__) */
