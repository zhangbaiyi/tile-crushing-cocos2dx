#include "StartScene.h"
#include "SelectScene.h"
#include "Settings.h"
#include "GameDefine.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
	return StartScene::create();
}

bool StartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto sprite = Sprite::create("start_background.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite, 0);

	Vector<MenuItem*> MenuItems;

	auto selectItem = MenuItemImage::create("Buttons/Start_Button.png", "Buttons/Start_Button_Clicked.png",
		[&](Ref* sender)
		{
			auto scene = SelectScene::createScene();
			Director::getInstance()->replaceScene(scene);
		});
	selectItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 6));
	MenuItems.pushBack(selectItem);

	auto settingsItem = MenuItemImage::create("Buttons/settings.png", "Buttons/settings_clicked.png",
		[&](Ref* sender)
		{
			auto scene = Settings::createScene();
			Director::getInstance()->replaceScene(scene);
		});
	settingsItem->setScale(0.5f);
	settingsItem->setPosition(Vec2(settingsItem->getContentSize().width/2, GAME_SCREEN_HEIGHT - settingsItem->getContentSize().height / 2));
	MenuItems.pushBack(settingsItem);

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);




	return true;
}