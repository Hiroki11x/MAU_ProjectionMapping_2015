//
//  BuildPC.hpp
//  MauInteractive
//
//  Created by 櫻木善将 on 2015/09/29.
//
//
#ifndef BuildPC_h
#define BuildPC_h
#include "ofMain.h"
#include "SceneElement.h"

class BuildPC :public SceneElement {
public:
    struct buildText {
        string text;
        int interval;
    };
    
    vector<buildText> buildTexts;
    int intervalFrame;
    int waitFrame;
    int textIndex;
    string displayText;
    ofTrueTypeFont drawer;
    
    BuildPC(){
        drawer.loadFont("Arial.ttf",30);
        this->displayText = "";
        this->buildTexts.push_back((buildText){"$ Hello,MAU!\n",10});
        this->buildTexts.push_back((buildText){"$ \n",30});
        this->buildTexts.push_back((buildText){"$ ",10});
        this->buildTexts.push_back((buildText){"s",10});
        this->buildTexts.push_back((buildText){"u",10});
        this->buildTexts.push_back((buildText){"d",10});
        this->buildTexts.push_back((buildText){"o",10});
        this->buildTexts.push_back((buildText){" ",10});
        this->buildTexts.push_back((buildText){".",10});
        this->buildTexts.push_back((buildText){" ",10});
        this->buildTexts.push_back((buildText){"/",10});
        this->buildTexts.push_back((buildText){"M",10});
        this->buildTexts.push_back((buildText){"a",10});
        this->buildTexts.push_back((buildText){"u",10});
        this->buildTexts.push_back((buildText){"/",10});
        this->buildTexts.push_back((buildText){"S",10});
        this->buildTexts.push_back((buildText){"p",10});
        this->buildTexts.push_back((buildText){"y",10});
        this->buildTexts.push_back((buildText){"\n",60});
        this->buildTexts.push_back((buildText){"$ passward",20});
        this->buildTexts.push_back((buildText){" 2",10});
        this->buildTexts.push_back((buildText){"0",10});
        this->buildTexts.push_back((buildText){"1",10});
        this->buildTexts.push_back((buildText){"5",10});
        this->buildTexts.push_back((buildText){"1",10});
        this->buildTexts.push_back((buildText){"0",10});
        this->buildTexts.push_back((buildText){"2",10});
        this->buildTexts.push_back((buildText){"4\n",60});
        this->buildTexts.push_back((buildText){"$ success!\n",30});
        this->buildTexts.push_back((buildText){"$ Application Building...\n",1000});
        this->waitFrame = 0;
        this->intervalFrame = 100;
        this->textIndex = 0;
    }
    
    virtual void draw() override;
    virtual void update() override;

};

#endif /* BuildPC_h */
