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

	auto sprite = Sprite::create("scene_sta.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite, 0);

	Vector<MenuItem*> MenuItems;

	auto ZenItem = MenuItemImage::create("btn_back01.png", "btn_back02.png",
		[&](Ref* sender)
	{
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	ZenItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 6));
	MenuItems.pushBack(ZenItem);

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}