#include "Settings.h"
#include "GameDefine.h"
#include "StartScene.h"

#include <iostream>
#include "ui/CocosGUI.h"
#include "ui/UISlider.h"
#include "ui/UIWidget.h"


USING_NS_CC;

Scene* Settings::createScene()
{
	auto scene = Scene::create();
	auto layer = Settings::create();
	scene->addChild(layer);
	return scene;
}

bool Settings::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto sprite = Sprite::create("setting_background.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite, 0);

	Vector<MenuItem*> MenuItems;

	auto backToMenuItem = MenuItemImage::create("Buttons/back_to_menu.png", "Buttons/back_to_menu_clicked.png",
		[&](Ref* sender)
		{
			auto scene = StartScene::createScene();
			Director::getInstance()->replaceScene(scene);
		});
	backToMenuItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 8));
	MenuItems.pushBack(backToMenuItem);
	
	auto musicOnItem = MenuItemImage::create("Buttons/music_on.png", "Buttons/music_on_clicked.png");
	auto musicOffItem = MenuItemImage::create("Buttons/music_off.png", "Buttons/music_off_clicked.png");
	auto menuToggleBackground = MenuItemToggle::createWithCallback([](Ref* obj) {   // lambda exp here is yet to study
		if (isBackgroundMusicPlay == true)
		{
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			isBackgroundMusicPlay = false;
			CCLOG("PAUSED");
		}
		else
		{
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			isBackgroundMusicPlay = true;
			CCLOG("RESUMED");
		}
		}, musicOnItem, musicOffItem, NULL);

	menuToggleBackground->setPosition(GAME_SCREEN_WIDTH / 2 - menuToggleBackground->getContentSize().width, GAME_SCREEN_HEIGHT / 4);
	

	auto effectsOnItem = MenuItemImage::create("Buttons/sound_effects_on.png", "Buttons/sound_effects_on_clicked.png");
	auto effectsOffItem = MenuItemImage::create("Buttons/sound_effects_off.png", "Buttons/sound_effects_off_clicked.png");
	auto menuToggleEffects = MenuItemToggle::createWithCallback([](Ref* obj) {   // lambda exp here is yet to study
		if (isEffectsPause == false)
		{
			
			isEffectsPause = true;
			SimpleAudioEngine::getInstance()->pauseAllEffects();
			CCLOG("PAUSED EFFECTS");
		}
		else
		{
			
			isEffectsPause = false;
			SimpleAudioEngine::getInstance()->resumeAllEffects();
			CCLOG("RESUMED EFFECTS");
		}
		}, effectsOnItem, effectsOffItem, NULL);
	menuToggleEffects->setPosition(GAME_SCREEN_WIDTH / 2 - menuToggleBackground->getContentSize().width, GAME_SCREEN_HEIGHT / 2);

	MenuItems.pushBack(menuToggleBackground);

	MenuItems.pushBack(menuToggleEffects);

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	createSliderBackground();
	createSliderEffects();


	return true;
}


void Settings::createSliderBackground() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto sl_background = Slider::create();
	sl_background->loadBarTexture("Slider/Slider_Back.png"); // what the slider looks like
	sl_background->loadSlidBallTextures("Slider/SliderNode_Normal.png", "Slider/SliderNode_Press.png", "Slider/SliderNode_Disable.png");
	sl_background->loadProgressBarTexture("Slider/Slider_PressBar.png");
	sl_background->setPosition(Point(GAME_SCREEN_WIDTH / 2 + sl_background->getContentSize().width/2, GAME_SCREEN_HEIGHT / 4));
	sl_background->setPercent(75);
	sl_background->addEventListener(CC_CALLBACK_2(Settings::SliderCallBackBackground, this));
	this->addChild(sl_background);


}

void Settings::SliderCallBackBackground(Ref* pSender, Slider::EventType type) {
	auto item = (Slider*)(pSender);
	log("%i", item->getPercent());
	//if (item->getPercent() == 100) {
	//	item->setEnabled(false);
	//}
	//else
	//{
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(item->getPercent() / 100.0f);
	//}
}

void Settings::createSliderEffects() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto sl_effects = Slider::create();
	sl_effects->loadBarTexture("Slider/Slider_Back.png"); // what the slider looks like
	sl_effects->loadSlidBallTextures("Slider/SliderNode_Normal.png", "Slider/SliderNode_Press.png", "Slider/SliderNode_Disable.png");
	sl_effects->loadProgressBarTexture("Slider/Slider_PressBar.png");
	sl_effects->setPosition(Point(GAME_SCREEN_WIDTH / 2 + sl_effects->getContentSize().width / 2, GAME_SCREEN_HEIGHT / 2));
	sl_effects->setPercent(75);
	sl_effects->addEventListener(CC_CALLBACK_2(Settings::SliderCallBackEffects, this));
	this->addChild(sl_effects);


}

void Settings::SliderCallBackEffects(Ref* pSender, Slider::EventType type) {
	auto item = (Slider*)(pSender);
	log("%i", item->getPercent());
	//if (item->getPercent() == 100) {
	//	item->setEnabled(false);
	//}
	//else
	//{
		SimpleAudioEngine::getInstance()->setEffectsVolume(item->getPercent() / 100.0f);
	//}
}

void Settings::menuCallBack() {
	auto scene = StartScene::createScene();
	auto transition = TransitionSlideInT::create(TRANSITION_TIME, scene);
	Director::getInstance()->replaceScene(transition);
}
