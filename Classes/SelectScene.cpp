#include "SelectScene.h"
#include "GameScene.h"
#include "GameDefine.h"
#include "StartScene.h"

USING_NS_CC;

int curModel;

Scene* SelectScene::createScene()
{
	return SelectScene::create();
}

bool SelectScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto sprite = Sprite::create("background_gamescene.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite, 0);

	Vector<MenuItem*> MenuItems;

	auto levelItem = MenuItemImage::create("Buttons/level.png", "Buttons/level_clicked.png",
		[&](Ref* sender)
		{
			curModel = RLIKE_MODEL;
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
		});
	levelItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 6 * 5));
	MenuItems.pushBack(levelItem);

	auto continueItem = MenuItemImage::create("Buttons/continue.png", "Buttons/continue_clicked.png",
		[&](Ref* sender)
		{
			curModel = CONTINUE_MODEL;
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
		});

	continueItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 6 * 4));
	MenuItems.pushBack(continueItem);

	auto generalItem = MenuItemImage::create("Buttons/general.png", "Buttons/general_clicked.png",
		[&](Ref* sender)
		{
			curModel = GENERAL_MODEL;
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
		});

	generalItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 6 * 3));
	MenuItems.pushBack(generalItem);

	auto ZenItem = MenuItemImage::create("Buttons/zen.png", "Buttons/zen_clicked.png",
		[&](Ref* sender)
		{
			curModel = ZEN_MODEL;
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
		});
	ZenItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 6 * 2));
	//MenuItems.pushBack(ZenItem);
	
	auto backToMenuItem = MenuItemImage::create("Buttons/back_to_menu_new.png", "Buttons/back_to_menu_new_clicked.png",
		[&](Ref* sender)
		{
			auto scene = StartScene::createScene();
			Director::getInstance()->replaceScene(scene);
		});
	backToMenuItem->setScale(1);
	backToMenuItem->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 6 - 50));
	MenuItems.pushBack(backToMenuItem);


	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Point(0,0));
	this->addChild(menu);



	

	return true;
}