

#include "general_time_up.h"
#include "GameDefine.h"
#include "GameScene.h"
#include "StartScene.h"


USING_NS_CC;
extern int generalCurScore;

Scene* timeUp::createScene()
{
    return timeUp::create();
}




bool timeUp::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    if (generalCurScore > UserDefault::getInstance()->getIntegerForKey("General"))
    {
        auto bg = cocos2d::Sprite::create("time_up_record.png");
        bg->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
        this->addChild(bg);
    }
    else
    {
        auto bg = cocos2d::Sprite::create("time_up.png");
        bg->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
        this->addChild(bg);
    }


    auto scoreLabel = Label::createWithTTF(std::to_string(1),"fonts/Marker Felt.ttf", 100);
    scoreLabel->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
    this->addChild(scoreLabel);


    Vector<MenuItem*> MenuItems;

    auto restartItem = MenuItemImage::create("Buttons/restart.png", "Buttons/restart_clicked.png",
        [&](Ref* sender)
        {
            auto scene = GameScene::createScene();
            Director::getInstance()->replaceScene(scene);
        }
        );
    restartItem->setScale(0.3);
    restartItem->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 4));
    MenuItems.pushBack(restartItem);

    auto homeItem = MenuItemImage::create("Buttons/back_to_home_new.png", "Buttons/back_to_home_new_clicked.png",
        [&](Ref* sender)
        {
            auto scene = StartScene::createScene();
            Director::getInstance()->replaceScene(scene);
        }
    );
    homeItem->setScale(0.3);
    homeItem->setPosition(Point(GAME_SCREEN_WIDTH / 2+100, GAME_SCREEN_HEIGHT / 6 ));
    MenuItems.pushBack(homeItem);

    auto menu = Menu::createWithArray(MenuItems);
    this->addChild(menu);

    return true;
}


