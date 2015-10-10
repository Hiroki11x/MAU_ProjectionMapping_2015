//
//  SoundManager.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/06.
//
//
#ifndef SoundManager_h
#define SoundManager_h

#include "ofMain.h"
class SoundManager{
public:
    static ofSoundPlayer soundPlayer;
    
    static void init();
    static void play();
    static void stop();
};
#endif