#include "PauseScene.h"
#include "GameDefine.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
	return PauseScene::create();
}

bool PauseScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto sprite = Sprite::create("scene_sta.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite, 0);

	Vector<MenuItem*> MenuItems;

	auto revertItem = MenuItemImage::create("btn_start01.png", "btn_start02.png",
		[&](Ref* sender)
	{
		Director::getInstance()->popScene();
	});
	revertItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 6));
	MenuItems.pushBack(revertItem);

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}