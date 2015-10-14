//
//  BaseImage.cpp
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/14.
//
//

#include "BaseImage.h"

ofImage BaseImage::generateImage(){
    ofImage img;
    img.allocate(100, 100, OF_IMAGE_COLOR);
    return  img;
}