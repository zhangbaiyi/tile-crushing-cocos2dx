#include "GameScene.h"
#include "PauseScene.h"
#include "EliminateSprite.h"
#include "GameDefine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
extern int curModel;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
		return false;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icons.plist");
	spriteSheet = SpriteBatchNode::create("icons.png");
	addChild(spriteSheet, 0);

	auto sprite = Sprite::create("background_gamescene.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite, -1);


	Vector<MenuItem*> MenuItems;
	MenuItemImage *pPauseItem = MenuItemImage::create("Buttons/pause.png", "Buttons/pause_clicked.png",
	[&](Ref* sender)
	{
		RenderTexture* renderTexture = RenderTexture::create(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);

		renderTexture->begin();
		this->visit();
		renderTexture->end();

		if (map.controller.model() == ZEN_MODEL && map.score() > UserDefault::getInstance()->getIntegerForKey("Zen"))
			UserDefault::getInstance()->setIntegerForKey("Zen", map.score());


		Director::getInstance()->pushScene(PauseScene::scene(renderTexture));
	});
	pPauseItem->setScale(0.20);
	pPauseItem->setPosition(Vec2(GAME_SCREEN_WIDTH - pPauseItem->getContentSize().width/2*0.1 -50,
		pPauseItem->getContentSize().height / 2*0.2 +50));

	MenuItems.pushBack(pPauseItem);


	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	limit = map.controller.create(curModel);

	TTFConfig config("fonts/arial.ttf", 30);
	auto labelLimit = Label::createWithTTF(config, StringUtils::format("%s: %d ", map.controller.getLimitType(), *limit));
	labelLimit->setPosition(Vec2(labelLimit->getContentSize().width, GAME_SCREEN_HEIGHT - labelLimit->getContentSize().height));
	labelLimit->setTag(11);
	this->addChild(labelLimit);
	auto labelScore = Label::createWithTTF(config, StringUtils::format("Score: %d ", map.score()));
	labelScore->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT - labelScore->getContentSize().height*2.6));
	labelScore->setTag(10);
	this->addChild(labelScore);
	
	//如果是闯关模式或继续游戏则Highest改为目标分数
	auto labelAim = Label::createWithTTF(config, StringUtils::format("Highest: %d ", map.controller.aim()));
	labelAim->setPosition(Vec2(GAME_SCREEN_WIDTH - labelAim->getContentSize().width, GAME_SCREEN_HEIGHT - labelAim->getContentSize().height));
	this->addChild(labelAim);

	initMap();
	scheduleUpdate();
	schedule(schedule_selector(GameScene::timeUpdate), 1.0f);

	return true;
}

void GameScene::timeUpdate(float dt)
{
	map.controller.timeUpdate();
}



void GameScene::initMap() 
{

	srand(static_cast<unsigned>(time(nullptr)));
	for (int i = 0; i != MAP_SIZE; ++i)
		createSprite(i);
}

void GameScene::createSprite(int pos) 
{
	EliminateSprite* spr = EliminateSprite::create();
	map.add(pos, spr);

	Point endPosition = map.positionOfItem(pos);
	Point startPosition = Point(endPosition.x, endPosition.y + GAME_SCREEN_HEIGHT / 2);
	spr->setPosition(startPosition);
	float speed = startPosition.y / (1.5 * GAME_SCREEN_HEIGHT);
	spr->runAction(MoveTo::create(speed, endPosition));
	
	spriteSheet->addChild(spr);
}

void GameScene::update(float t)
{
	if (!map.actionJudge())
		checkSprite();
	if (limit == 0)
	{
		//结束动画
		if (map.controller.model() == GENERAL_MODEL && map.score() > UserDefault::getInstance()->getIntegerForKey("General"))
			UserDefault::getInstance()->setIntegerForKey("General", map.score());
		if (map.controller.model() == RLIKE_MODEL || map.controller.model() == CONTINUE_MODEL)
		{
			if (map.score() >= map.controller.aim())
			{
				int tmp = cocos2d::UserDefault::getInstance()->getIntegerForKey("Level");
				cocos2d::UserDefault::getInstance()->setIntegerForKey("Level", tmp + LEVEL_CHANGE);
				
				srand(static_cast<unsigned>(time(nullptr)));
				int changeScore = rand() % TOTAL_SPRITE;
				std::ostringstream buffer;
				buffer << "Score" << changeScore;
				tmp = cocos2d::UserDefault::getInstance()->getIntegerForKey(buffer.str().c_str());
				cocos2d::UserDefault::getInstance()->setIntegerForKey(buffer.str().c_str(), tmp + SCORE_CHANGE);
				//进入下一关的准备界面
			}
			else
			{
				cocos2d::UserDefault::getInstance()->setIntegerForKey("Level", 1);
				for (int i = 0; i != TOTAL_SPRITE; ++i)
				{
					std::ostringstream buffer;
					buffer << "Score" << i;
					cocos2d::UserDefault::getInstance()->setIntegerForKey(buffer.str().c_str(), 1);
				}
			}
		}
		//游戏结束
	}

	if(limit > 0)
	{
		Label *labelLimit = (Label *)this->getChildByTag(11);
		labelLimit->setString(StringUtils::format("%s: %d ", map.controller.getLimitType(), *limit));
		Label *labelScore = (Label *)this->getChildByTag(10);
		labelScore->setString(StringUtils::format("Score: %d ", map.score()));
	}
}

void GameScene::checkSprite()
{
	if (map.check())
	{
		std::vector<int> emptyRow = map.fill();
		for (int col = 0; col < COLS; ++col)
			for (int pos = col + (ROWS - emptyRow[col]) * COLS; pos < MAP_SIZE; pos += COLS)
				createSprite(pos);
	}
}


bool GameScene::onTouchBegan(Touch *touch, Event *unused)
{
	staPosition = -1;

	if (map.canTouch()) 
	{
		auto location = touch->getLocation();
		staPosition = map.spriteOfPoint(&location);
	}
	return map.canTouch();
}

void GameScene::onTouchMoved(Touch *touch, Event *unused) 
{
	if (staPosition < 0 || !map.canTouch())
		return;

	int row = staPosition / COLS;
	int col = staPosition % COLS;

	auto location = touch->getLocation();
	auto endPosition = map.spriteOfPoint(&location);
	map.swap(staPosition, endPosition);
}