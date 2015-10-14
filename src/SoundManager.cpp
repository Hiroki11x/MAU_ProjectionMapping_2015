//
//  SoundManager.cpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/06.
//
//
#include "SoundManager.h"

ofSoundPlayer SoundManager::soundPlayer;

void SoundManager::init(){
    soundPlayer.loadSound("mau_music_sample03.mp3");
    soundPlayer.setLoop(true);
}

void SoundManager::play(){
    soundPlayer.play();
}

void SoundManager::stop(){
    soundPlayer.stop();
}