#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "cocos2d.h"

#include "ui/CocosGUI.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace ui;

using namespace CocosDenshion;

class Settings :public Layer {

public:

    static Scene* createScene();

    virtual bool init();


    void menuCallBack();

    void createSliderBackground();

    void SliderCallBackBackground(Ref* pSender, Slider::EventType type);

    void createSliderEffects();

    void SliderCallBackEffects(Ref* pSender, Slider::EventType type);

    CREATE_FUNC(Settings);

};


#endif