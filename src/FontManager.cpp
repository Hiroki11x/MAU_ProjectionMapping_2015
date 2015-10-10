//
//  FontManager.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/10.
//
//

#include "FontManager.h"

void FontManager::loadFont(string arg, int size){
    mfont.loadFont(arg, size);
}

void FontManager::drawString(string arg ,float x, float y){
    mfont.drawString(arg, x, y);
}