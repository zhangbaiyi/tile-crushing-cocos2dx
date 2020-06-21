

#include "level_fail.h"
#include "GameDefine.h"
#include "GameScene.h"

USING_NS_CC;

Scene* levelFail::createScene()
{
    return levelFail::create();
}




bool levelFail::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto bg = cocos2d::Sprite::create("level_fail.png");
    bg->setPosition(Point(GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2));
    this->addChild(bg);

    auto revertItem = MenuItemImage::create("Buttons/restart.png", "Buttongs/restart_clicked.png", [&](Ref* sender)
        {
            auto scene = GameScene::createScene();
            Director::getInstance()->replaceScene(scene);
        });

    revertItem->setScale(0.3);

    auto menu = Menu::create(revertItem);
    menu->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
    this->addChild(menu);

    return true;
}


