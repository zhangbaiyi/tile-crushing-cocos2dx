#include "PauseScene.h"
#include "GameDefine.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
	return PauseScene::create();
}

Scene* PauseScene::createScene(RenderTexture* screenShot, bool isFlip)
{
	Layer* p_scene = Layer::create();
	Sprite* _screenShot = Sprite::createWithTexture(screenShot->getSprite()->getTexture());
	_screenShot->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	_screenShot->setFlippedY(isFlip);
	_screenShot->setColor(Color3B::GRAY);
	p_scene->addChild(_screenShot);

	PauseScene* pScene = PauseScene::create();
	pScene->addChild(p_scene);

	return pScene;

}

bool PauseScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto sprite = Sprite::create("background_gamescene.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite, 0);

	Vector<MenuItem*> MenuItems;

	auto revertItem = MenuItemImage::create("Buttons/resume.png", "Buttons/general_clicked.png",
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