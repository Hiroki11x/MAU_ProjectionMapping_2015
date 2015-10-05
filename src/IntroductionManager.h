//
//  IntroductionManager.hpp
//  MauInteractiv*e
//
//  Created by 櫻木善将 on 2015/09/29.
//
//

#ifndef IntroductionManager_h
#define IntroductionManager_h

#include "ofMain.h"
#include "SceneElement.h"
#include "SceneManager.h"
#include "BuildPC.h"
#include "textExplosion.h"
#include "Fadeout.h"
#include "Loading.h"

class IntroductionManager : public SceneManager {
public:
    virtual void setup() override;
};

#endif