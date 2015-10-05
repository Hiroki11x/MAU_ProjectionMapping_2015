//
//  FindTarget.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/10/03.
//
//

#ifndef FindTarget_h
#define FindTarget_h

#include "SceneElement.h"

class FindTarget : public SceneElement {
public:
    virtual void update() override;
    virtual void draw() override;
    virtual void init() override;
    virtual void end() override;
    
    

};
#endif
