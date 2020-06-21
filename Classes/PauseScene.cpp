#include "PauseScene.h"
#include "GameDefine.h"
#include "GameScene.h"
#include "StartScene.h"
#include "pSettings.h"

USING_NS_CC;



Scene* PauseScene::scene(RenderTexture* screenShot)
{
	Scene* p_scene = Scene::create();
	Sprite* _screenShot = Sprite::createWithTexture(screenShot->getSprite()->getTexture());
	_screenShot->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	_screenShot->setFlippedY(true);
	_screenShot->setColor(Color3B::GRAY);
	p_scene->addChild(_screenShot);

	PauseScene* layer = PauseScene::create();
	p_scene->addChild(layer);



	return p_scene;

}

bool PauseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}



	Vector<MenuItem*> MenuItems;

	MenuItemImage* resumeItem = MenuItemImage::create("Buttons/resume.png", "Buttons/resume_clicked.png",
		[&](Ref* sender)
		{
			Director::getInstance()->popScene();
		});

	resumeItem->setScale(0.25);
	resumeItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	MenuItems.pushBack(resumeItem);

	MenuItemImage* restartItem = MenuItemImage::create("Buttons/restart.png", "Buttons/restart_clicked.png",
		[&](Ref* sender)
		{
			Director::getInstance()->replaceScene(GameScene::createScene());
		});

	restartItem->setScale(0.25);
	restartItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2 + restartItem->getContentSize().height*0.3 ));
	MenuItems.pushBack(restartItem);

	MenuItemImage* backItem = MenuItemImage::create("Buttons/back_to_menu_new.png", "Buttons/back_to_menu_new_clicked.png",
		[&](Ref* sender)
		{
			Director::getInstance()->replaceScene(StartScene::createScene());
		});

	backItem->setScale(0.20);
	backItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2 - backItem->getContentSize().height * 0.45 ));
	MenuItems.pushBack(backItem);

	MenuItemImage* settingsItem = MenuItemImage::create("Buttons/settings.png", "Buttons/settings_clicked.png",
		[&](Ref* sender)
		{
			Director::getInstance()->pushScene(pSettings::createScene());
		});

	settingsItem->setScale(0.25);
	settingsItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2 - restartItem->getContentSize().height * 0.3));
	MenuItems.pushBack(settingsItem);

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);

	return true;
}