#ifndef __PSETTINGS_H__
#define __PSETTINGS_H__

#include "cocos2d.h"

#include "ui/CocosGUI.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace ui;

using namespace CocosDenshion;

class pSettings :public Layer {

public:

    static Scene* createScene();

    virtual bool init();

    void pSettings::menuMusicCallback(cocos2d::Ref* pSender);

    void pSettings::menuBack(cocos2d::Ref* pSender);

    void createSliderBackground();

    void SliderCallBackBackground(Ref* pSender, Slider::EventType type);

    void createSliderEffects();

    void SliderCallBackEffects(Ref* pSender, Slider::EventType type);

    CREATE_FUNC(pSettings);

};


#endif