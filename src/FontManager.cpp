//
//  FontManager.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/10.
//
//

#include "FontManager.h"

ofxTrueTypeFontUL2 FontManager::mfont;
ofxTrueTypeFontUL2 FontManager::msmallfont;
ofxTrueTypeFontUL2 FontManager::mbigfont;

void FontManager::loadFont(string arg, int size){
    mfont.loadFont(arg, size);
}

void FontManager::drawString(string arg ,float x, float y){
    mfont.drawString(arg, x, y);
}

void FontManager::loadSmallFont(string arg, int size){
    msmallfont.loadFont(arg, size);
}

void FontManager::drawSmallString(string arg ,float x, float y){
    msmallfont.drawString(arg, x, y);
}

void FontManager::loadBigFont(string arg, int size){
    mbigfont.loadFont(arg, size);
}

void FontManager::drawBigString(string arg ,float x, float y){
    mbigfont.drawString(arg, x, y);
}