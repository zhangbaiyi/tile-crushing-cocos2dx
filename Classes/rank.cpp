

#include "rank.h"
#include "GameDefine.h"
#include"StartScene.h"

USING_NS_CC;

Scene* rank::createScene()
{
    return rank::create();
}


bool rank::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create("rank.png");
    bg->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
    this->addChild(bg);

    int zenBest = UserDefault::getInstance()->getIntegerForKey("Zen");
    int levelBest = UserDefault::getInstance()->getIntegerForKey("Level");
    int generalBest = UserDefault::getInstance()->getIntegerForKey("General");

    auto zenBestLabel = Label::createWithTTF(std::to_string(zenBest), "fonts/Marker Felt.ttf", zen_best_size);
    zenBestLabel->setTextColor(Color4B::RED);
    zenBestLabel->setPosition(Point(zen_best_x,zen_best_y ));
    this->addChild(zenBestLabel);
    
    auto levelBestLabel = Label::createWithTTF(std::to_string(levelBest), "fonts/Marker Felt.ttf", level_best_size);
    levelBestLabel->setTextColor(Color4B::RED);
    levelBestLabel->setPosition(Point(level_best_x, level_best_y));
   
    this->addChild(levelBestLabel);

    auto generalBestLabel = Label::createWithTTF(std::to_string(generalBest), "fonts/Marker Felt.ttf", gen_best_size);
    generalBestLabel->setTextColor(Color4B::RED);
    generalBestLabel->setPosition(Point(gen_best_x, gen_best_y));

    this->addChild(generalBestLabel);

    Vector<MenuItem*> MenuItems;
    auto backToMenuItem = MenuItemImage::create("Buttons/back_to_menu_new.png", "Buttons/back_to_menu_new_clicked.png",
        [&](Ref* sender)
        {
            auto scene = StartScene::createScene();
            Director::getInstance()->replaceScene(scene);
        });
    backToMenuItem->setScale(1);
    backToMenuItem->setPosition(Point(-GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 6 ));
    MenuItems.pushBack(backToMenuItem);

    auto menu = Menu::createWithArray(MenuItems);
    this->addChild(menu);

    return true;
}


