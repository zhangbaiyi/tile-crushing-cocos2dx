

#include "level_trans.h"
#include "GameDefine.h"
#include "GameScene.h"

USING_NS_CC;

Scene* levelTrans::createScene()
{
    return levelTrans::create();
}




bool levelTrans::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto bg = cocos2d::Sprite::create("level_trans.png");
    bg->setPosition(Point(GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2));
    this->addChild(bg);

    auto levelNumLabel = Label::createWithTTF(std::to_string(2), "fonts/Marker Felt.ttf", level_num_label_size );
    levelNumLabel->setPosition(Point(level_num_label_width, GAME_SCREEN_HEIGHT - level_num_label_height));
    levelNumLabel->setColor(Color3B::YELLOW);
    this->addChild(levelNumLabel);

    auto levelStepLabel = Label::createWithTTF(std::to_string(2), "fonts/Marker Felt.ttf", level_step_label_size);
    levelStepLabel->setPosition(Point(level_step_label_width, GAME_SCREEN_HEIGHT - level_step_label_height));
    levelStepLabel->setColor(Color3B::YELLOW);
    this->addChild(levelStepLabel);

    auto levelScoreLabel = Label::createWithTTF(std::to_string(2), "fonts/Marker Felt.ttf", level_score_label_size);
    levelScoreLabel->setPosition(Point(level_score_label_width, GAME_SCREEN_HEIGHT - level_score_label_height));
    levelScoreLabel->setColor(Color3B::YELLOW);
    this->addChild(levelScoreLabel);

    auto levelBonusLabel = Label::createWithTTF(std::to_string(2), "fonts/Marker Felt.ttf", level_bonus_label_size);
    levelBonusLabel->setPosition(Point(level_bonus_label_width, GAME_SCREEN_HEIGHT - level_bonus_label_height));
    levelBonusLabel->setColor(Color3B::YELLOW);
    this->addChild(levelBonusLabel);

    return true;
}


void levelTrans::nextLevel(float dt)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_LEVEL, scene));
}