#include "SelectScene.h"
#include "GameScene.h"
#include "GameDefine.h"

USING_NS_CC;

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

	auto ZenItem = MenuItemImage::create("Buttons/zen.png", "Buttons/zen_clicked.png",
		[&](Ref* sender)
		{
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
		});
	ZenItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 6));
	MenuItems.pushBack(ZenItem);

	auto GenItem = MenuItemImage::create("Buttons/general.png", "Buttons/general_clicked.png",
		[&](Ref* sender)
		{
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);
		});
	GenItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 4));
	MenuItems.pushBack(GenItem);

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}