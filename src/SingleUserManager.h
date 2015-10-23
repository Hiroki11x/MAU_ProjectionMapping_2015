//
//  SingleUserManager.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/18.
//
//

#ifndef __mauInteractive__SingleUserManager__
#define __mauInteractive__SingleUserManager__

#include "ofMain.h"
#include "SingleAgent.h"

class SingleUserManager{
private:
public:
    static vector<SingleAgent *> user_agent;
    static int json_num;
//    static SingleUserManager &getInstance();
};


#endif /* defined(__mauInteractive__SingleUserManager__) */
