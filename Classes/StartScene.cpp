#include "StartScene.h"
#include "SelectScene.h"
#include "Settings.h"
#include "GameDefine.h"
#include "rank.h"

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

	UserDefault::getInstance()->setIntegerForKey("Level", 1);


	auto sprite = Sprite::create("start_background.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite, 0);

	Vector<MenuItem*> MenuItems;



	auto selectItem = MenuItemImage::create("Buttons/start.png", "Buttons/start_clicked.png",
		[&](Ref* sender)
		{
			auto scene = SelectScene::createScene();
			Director::getInstance()->replaceScene(scene);
		});
	selectItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2 , GAME_SCREEN_HEIGHT / 4));
	selectItem->setScale(0.4);
	MenuItems.pushBack(selectItem);

	auto settingsItem = MenuItemImage::create("Buttons/settings.png", "Buttons/settings_clicked.png",
		[&](Ref* sender)
		{
			auto scene = Settings::createScene();
			Director::getInstance()->replaceScene(scene);
		});
	settingsItem->setScale(0.2);
	settingsItem->setPosition(Vec2(GAME_SCREEN_WIDTH/2 - settingsItem->getContentSize().width*0.28, GAME_SCREEN_HEIGHT/6 ));
	MenuItems.pushBack(settingsItem);

	auto rankItem = MenuItemImage::create("Buttons/rank_new.png", "Buttons/rank_new_clicked.png",
		[&](Ref* sender)
		{
			auto scene = rank::createScene();
			Director::getInstance()->replaceScene(scene);
		});
	rankItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2 + rankItem->getContentSize().width * 0.20, GAME_SCREEN_HEIGHT / 6));
	rankItem->setScale(0.20);
	MenuItems.pushBack(rankItem);

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);




	return true;
}