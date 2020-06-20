#include "pSettings.h"
#include "GameDefine.h"
#include "StartScene.h"

#include <iostream>
#include "ui/CocosGUI.h"
#include "ui/UISlider.h"
#include "ui/UIWidget.h"


USING_NS_CC;

Scene* pSettings::createScene()
{
	auto scene = Scene::create();
	auto layer = pSettings::create();
	scene->addChild(layer);
	return scene;
}

bool pSettings::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto sprite = Sprite::create("setting_background.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite, 0);

	Vector<MenuItem*> MenuItems;

	auto backItem = MenuItemImage::create("Buttons/back.png", "Buttons/back_clicked.png",
		[&](Ref* sender)
		{
			pSettings::menuBack(sender);
		});
	backItem->setScale(0.15);
	backItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 8));
	MenuItems.pushBack(backItem);


	auto musicOnItem = MenuItemImage::create("Buttons/music_on.png", "Buttons/music_on_clicked.png");
	auto musicOffItem = MenuItemImage::create("Buttons/music_off.png", "Buttons/music_off_clicked.png");

	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY) == true)
	{
		log(MUSIC_KEY);
	}
	else { log("MUSIC_KEY FALSE"); }

	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY) == true)
	{
		log(SOUND_KEY);
	}
	else { log("SOUND_KEY FALSE"); }

	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY) == true)
	{
		auto menuToggleBackground = MenuItemToggle::createWithCallback([](Ref* pSender) {   // lambda exp here is yet to study
			auto item = (MenuItemToggle*)pSender;

			if (item->getSelectedIndex() == 1) {
				UserDefault::getInstance()->setBoolForKey(MUSIC_KEY, false);
				SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			}
			else {
				SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
				UserDefault::getInstance()->setBoolForKey(MUSIC_KEY, true);
			}

			}, musicOnItem, musicOffItem, NULL);

		menuToggleBackground->setPosition(GAME_SCREEN_WIDTH / 2-50, GAME_SCREEN_HEIGHT / 4);
		MenuItems.pushBack(menuToggleBackground);
	}

	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY) == false)
	{
		auto menuToggleBackground = MenuItemToggle::createWithCallback([](Ref* pSender) {   // lambda exp here is yet to study
			auto item = (MenuItemToggle*)pSender;

			if (item->getSelectedIndex() == 1) {
				UserDefault::getInstance()->setBoolForKey(MUSIC_KEY, true);
				SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			}
			else {
				SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
				UserDefault::getInstance()->setBoolForKey(MUSIC_KEY, false);
			}

			}, musicOffItem, musicOnItem, NULL);

		menuToggleBackground->setPosition(GAME_SCREEN_WIDTH / 2-50, GAME_SCREEN_HEIGHT / 4);
		MenuItems.pushBack(menuToggleBackground);
	}
	auto effectsOnItem = MenuItemImage::create("Buttons/sound_effects_on.png", "Buttons/sound_effects_on_clicked.png");
	auto effectsOffItem = MenuItemImage::create("Buttons/sound_effects_off.png", "Buttons/sound_effects_off_clicked.png");

	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY) == true)
	{

		auto menuToggleEffects = MenuItemToggle::createWithCallback([](Ref* pSender) {   // lambda exp here is yet to study
			auto item = (MenuItemToggle*)pSender;
			log("toggle item %d", item->getSelectedIndex());

			if (item->getSelectedIndex() == 1) {
				UserDefault::getInstance()->setBoolForKey(SOUND_KEY, false);
			}
			else {

				UserDefault::getInstance()->setBoolForKey(SOUND_KEY, true);
			}

			}, effectsOnItem, effectsOffItem, NULL);
		menuToggleEffects->setPosition(GAME_SCREEN_WIDTH / 2-50, GAME_SCREEN_HEIGHT / 2);
		MenuItems.pushBack(menuToggleEffects);
	}

	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY) == false)
	{

		auto menuToggleEffects = MenuItemToggle::createWithCallback([](Ref* pSender) {   // lambda exp here is yet to study
			auto item = (MenuItemToggle*)pSender;
			log("toggle item %d", item->getSelectedIndex());

			if (item->getSelectedIndex() == 1) {
				UserDefault::getInstance()->setBoolForKey(SOUND_KEY, true);
			}
			else {

				UserDefault::getInstance()->setBoolForKey(SOUND_KEY, false);
			}

			}, effectsOffItem, effectsOnItem, NULL);
		menuToggleEffects->setPosition(GAME_SCREEN_WIDTH / 2-50, GAME_SCREEN_HEIGHT / 2);
		MenuItems.pushBack(menuToggleEffects);
	}

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	createSliderBackground();
	createSliderEffects();


	return true;
}


void pSettings::createSliderBackground() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto sl_background = Slider::create();
	sl_background->loadBarTexture("Slider/Slider_Back.png"); // what the slider looks like
	sl_background->loadSlidBallTextures("Slider/SliderNode_Normal.png", "Slider/SliderNode_Press.png", "Slider/SliderNode_Disable.png");
	sl_background->loadProgressBarTexture("Slider/Slider_PressBar.png");
	sl_background->setPosition(Point(GAME_SCREEN_WIDTH / 2 + sl_background->getContentSize().width / 2, GAME_SCREEN_HEIGHT / 4));
	sl_background->setPercent(SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() * 100.0f);
	sl_background->addEventListener(CC_CALLBACK_2(pSettings::SliderCallBackBackground, this));
	this->addChild(sl_background);


}

void pSettings::SliderCallBackBackground(Ref* pSender, Slider::EventType type) {
	auto item = (Slider*)(pSender);
	log("%i", item->getPercent());
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(item->getPercent() / 100.0f);
}

void pSettings::createSliderEffects() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto sl_effects = Slider::create();
	sl_effects->loadBarTexture("Slider/Slider_Back.png"); // what the slider looks like
	sl_effects->loadSlidBallTextures("Slider/SliderNode_Normal.png", "Slider/SliderNode_Press.png", "Slider/SliderNode_Disable.png");
	sl_effects->loadProgressBarTexture("Slider/Slider_PressBar.png");
	sl_effects->setPosition(Point(GAME_SCREEN_WIDTH / 2 + sl_effects->getContentSize().width / 2, GAME_SCREEN_HEIGHT / 2));
	sl_effects->setPercent(SimpleAudioEngine::getInstance()->getEffectsVolume() * 100.0f);
	sl_effects->addEventListener(CC_CALLBACK_2(pSettings::SliderCallBackEffects, this));
	this->addChild(sl_effects);


}

void pSettings::SliderCallBackEffects(Ref* pSender, Slider::EventType type) {
	auto item = (Slider*)(pSender);
	log("%i", item->getPercent());
	SimpleAudioEngine::getInstance()->setEffectsVolume(item->getPercent() / 100.0f);
}

void pSettings::menuBack(cocos2d::Ref* pSender) {
	Director::getInstance()->popScene();
}
