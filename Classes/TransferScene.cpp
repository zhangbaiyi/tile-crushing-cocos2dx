#include "TransferScene.h"
#include "GameScene.h"
#include "GameDefine.h"
#include <vector>

USING_NS_CC;
extern bool isBreakThrough;
extern int curModel;

int changeScore = -1;

Scene* TransferScene::createScene()
{
	return TransferScene::create();
}

bool TransferScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Sprite* sprite;
	Vector<MenuItem*> MenuItems;
	MenuItemImage* restartOrNextItem;

	if (isBreakThrough)
	{
		srand(static_cast<unsigned>(time(nullptr)));
		int changeScore = rand() % TOTAL_SPRITE;
		sprite = Sprite::create("level_pass.png");
		restartOrNextItem = MenuItemImage::create("Buttons/next.png", "Buttons/next_clicked.png",
			CC_CALLBACK_1(TransferScene::nextCallBack, this));
	}
	else
	{
		sprite = Sprite::create("level_pass.png");
		restartOrNextItem = MenuItemImage::create("Buttons/restart.png", "Buttons/restart_clicked.png",
			CC_CALLBACK_1(TransferScene::returnToStartCallBack, this));
	}
	sprite->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
	this->addChild(sprite, 0);

	restartOrNextItem->setPosition(Point(50,50)); //从头开始或下一关的位置
	
	MenuItems.pushBack(restartOrNextItem);


	auto restartItem = MenuItemImage::create("Buttons/prev.png", "Buttons/prev_clicked.png",
		[&](Ref* sender)
	{
		curModel = CONTINUE_MODEL;
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	restartItem->setPosition(Point(-50,50));  //重新开始的位置
	
	MenuItems.pushBack(restartItem);
	
	std::vector<Vec2> spriteScoreLocation(TOTAL_SPRITE);
	std::vector<Label*> sprteScoreLabel(TOTAL_SPRITE, nullptr);
	//写入所有点的坐标
	for (int i = 0; i != TOTAL_SPRITE; ++i)
	{
		std::ostringstream buffer;
		buffer << "Score" << i;
		int score = cocos2d::UserDefault::getInstance()->getIntegerForKey(buffer.str().c_str());
		if (isBreakThrough && i == changeScore)
		{
			score += SCORE_CHANGE;
			sprteScoreLabel[i] = Label::createWithTTF(StringUtils::format(" %d", score),"fonts/Marker Felt.ttf",27);//改变的分数
			sprteScoreLabel[i]->setTextColor(Color4B::RED);
		}
		else
			sprteScoreLabel[i] = Label::createWithTTF(StringUtils::format("%d", score), "fonts/Marker Felt.ttf",27);

		sprteScoreLabel[i]->setPosition(spriteScoreLocation[i]);
		this->addChild(sprteScoreLabel[i]);
	}
	int level = cocos2d::UserDefault::getInstance()->getIntegerForKey("Level");
	int step = isBreakThrough ? LEVEL_TO_STEP(level + 1) : LEVEL_TO_STEP(level);


	auto curLevel = Label::createWithTTF(std::to_string(level), "fonts/Marker Felt.ttf", level_trans_current_label_size);
	curLevel->setPosition(Point(level_trans_current_label_width, level_trans_current_label_height));
	this->addChild(curLevel);

	auto bestStep = Label::createWithTTF(std::to_string(UserDefault::getInstance()->getIntegerForKey("Level")), "fonts/Marker Felt.ttf", level_trans_best_label_size);
	bestStep->setPosition(Point(level_trans_best_label_width, level_trans_best_label_height));
	this->addChild(bestStep);

	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu);

	return true;
}

void TransferScene::nextCallBack(Ref* pSender)
{
	int tmp = cocos2d::UserDefault::getInstance()->getIntegerForKey("Level");
	cocos2d::UserDefault::getInstance()->setIntegerForKey("Level", tmp + LEVEL_CHANGE);

	std::ostringstream buffer;
	buffer << "Score" << changeScore;
	tmp = cocos2d::UserDefault::getInstance()->getIntegerForKey(buffer.str().c_str());
	cocos2d::UserDefault::getInstance()->setIntegerForKey(buffer.str().c_str(), tmp + SCORE_CHANGE);
}

void TransferScene::returnToStartCallBack(Ref* pSender)
{
	cocos2d::UserDefault::getInstance()->setIntegerForKey("Level", 1);
	for (int i = 0; i != TOTAL_SPRITE; ++i)
	{
		std::ostringstream buffer;
		buffer << "Score" << i;
		cocos2d::UserDefault::getInstance()->setIntegerForKey(buffer.str().c_str(), 1);
		curModel = CONTINUE_MODEL;
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}