

#include "level_pass.h"
#include "GameDefine.h"
#include "level_trans.h"

USING_NS_CC;

Scene* levelPass::createScene()
{
    return levelPass::create();
}




bool levelPass::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto bg = cocos2d::Sprite::create("level_pass.png");
    bg->setPosition(Point(GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2));
    this->addChild(bg);

    auto nextItem = MenuItemImage::create("Buttons/next.png", "Buttongs/next_clicked.png", [&](Ref* sender)
        {
            auto scene = levelTrans::createScene();
            Director::getInstance()->replaceScene(scene);
        });
    nextItem->setScale(0.3);


    auto menu = Menu::create(nextItem);
    menu->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
    this->addChild(menu);

    return true;
}


