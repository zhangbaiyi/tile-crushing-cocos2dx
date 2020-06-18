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
	_screenShot->setFlippedY(TRUE);
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
			PauseScene::menuContinueCallback(sender);
		});
	resumeItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	MenuItems.pushBack(resumeItem);

	MenuItemImage* restartItem = MenuItemImage::create("Buttons/restart.png", "Buttons/restart_clicked.png",
		[&](Ref* sender)
		{
			PauseScene::menuRestart(sender);
		});
	restartItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2 + restartItem->getContentSize().height*1.5));
	MenuItems.pushBack(restartItem);

	MenuItemImage* backItem = MenuItemImage::create("Buttons/back_to_menu.png", "Buttons/back_to_menu_clicked.png",
		[&](Ref* sender)
		{
			PauseScene::menuBack(sender);
		});
	backItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2 - backItem->getContentSize().height * 1.5));
	MenuItems.pushBack(backItem);

	MenuItemImage* settingsItem = MenuItemImage::create("Buttons/settings.png", "Buttons/settings_clicked.png",
		[&](Ref* sender)
		{
			PauseScene::menuSettings(sender);
		});
	settingsItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2 - settingsItem->getContentSize().height * 3.0 ));
	MenuItems.pushBack(settingsItem);

	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);

	return true;
}

void PauseScene::menuContinueCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

void PauseScene::menuRestart(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void PauseScene::menuBack(Ref* pSender)
{
	Director::getInstance()->replaceScene(StartScene::createScene());
}

void PauseScene::menuSettings(Ref* pSender)
{
	Director::getInstance()->pushScene(pSettings::createScene());
}