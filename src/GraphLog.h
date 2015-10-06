//
//  GraphLog.h
//  mauInteractive
//
//  Created by HirokiNaganuma on 2015/10/05.
//
//

#ifndef __mauInteractive__GraphLog__
#define __mauInteractive__GraphLog__

#include "ofMain.h"
#define MAX_ASSIGN 200

class GraphLog{
    
private:
    
    vector <float> valHistory;
    
    float max_value;
    float height_limit;
    bool isGetValue;
    
public:
    void setup();
    void update(float arg);
    void draw();
    void set_height_limit(float arg);
    
    void keyPressed(int key);
};

#endif /* defined(__mauInteractive__GraphLog__) */
