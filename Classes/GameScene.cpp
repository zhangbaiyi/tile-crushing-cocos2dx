#include "GameScene.h"
#include "PauseScene.h"
#include "EliminateSprite.h"
#include "GameDefine.h"
#include "SimpleAudioEngine.h"
#include "general_time_up.h"
#include "TransferScene.h"
#include "StartScene.h"

USING_NS_CC;
using namespace CocosDenshion;
extern int curModel;
int generalCurScore;
bool isBreakThrough = false;
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


	if (curModel == RLIKE_MODEL||curModel == CONTINUE_MODEL)
	{
		auto sprite = Sprite::create("level_gamescene.png");
		sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
		this->addChild(sprite, -1);
	}

	if (curModel == GENERAL_MODEL)
	{
		auto sprite = Sprite::create("general_background.png");
		sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
		this->addChild(sprite, -1);
	}

	if(curModel == ZEN_MODEL)
	{
		auto sprite = Sprite::create("zen_gamescene.png");
		sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
		this->addChild(sprite, -1);
	}


	Vector<MenuItem*> MenuItems;
	MenuItemImage* pPauseItem = MenuItemImage::create("Buttons/pause.png", "Buttons/pause_clicked.png",
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
	pPauseItem->setPosition(Vec2(GAME_SCREEN_WIDTH - pPauseItem->getContentSize().width / 2 * 0.1 - 50,
		pPauseItem->getContentSize().height / 2 * 0.2 + 50));

	MenuItems.pushBack(pPauseItem);




	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	if (curModel == ZEN_MODEL)
	{

		auto labelScore = Label::createWithTTF(std::to_string(map.score()), "fonts/Marker Felt.ttf", zen_score_size);
		labelScore->setPosition(Point(zen_score_width, zen_score_height));
		labelScore->setTag(12);
		this->addChild(labelScore);
	}
	else {
	
		limit = map.controller.create(curModel);

		auto labelLimit = Label::createWithTTF(StringUtils::format("%d", *limit), "fonts/Marker Felt.ttf", left_up_label_size);
		labelLimit->setPosition(Point(left_up_label_width, left_up_label_height));
		labelLimit->setTag(11);
		this->addChild(labelLimit);
		auto labelScore = Label::createWithTTF(StringUtils::format("%d", map.score()), "fonts/Marker Felt.ttf", right_up_label_size);
		labelScore->setPosition(Point(right_up_label_width, right_up_label_height));
		labelScore->setTag(10);
		this->addChild(labelScore);
		auto labelAim = Label::createWithTTF(StringUtils::format("%d", map.controller.aim()), "fonts/Marker Felt.ttf", aim_label_size);
		labelAim->setPosition(Point(aim_label_width, aim_label_height));
		labelAim->setColor(Color3B::RED);

		this->addChild(labelAim);
	
	}

	
	//如果是闯关模式或继续游戏则Highest改为目标分数
	
	initMap();
	scheduleUpdate();
	schedule(CC_SCHEDULE_SELECTOR(GameScene::timeUpdate), 1.0f);

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

	if (*limit == 0)
	{
		if (curModel == GENERAL_MODEL)
		{
			generalCurScore = map.score();
			UserDefault::getInstance()->setIntegerForKey("General", map.score());
			auto scene = StartScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	
		if (map.controller.model() == RLIKE_MODEL || map.controller.model() == CONTINUE_MODEL)
		{
			if (map.score() < map.controller.aim())
				isBreakThrough = false;
			else
				isBreakThrough = true;
			auto scene = TransferScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	}

	if (limit > 0)
	{
		Label* labelLimit = (Label*)this->getChildByTag(11);
		labelLimit->setString(StringUtils::format(" %d ",  *limit));
		Label* labelScore = (Label*)this->getChildByTag(10);
		labelScore->setString(StringUtils::format(" %d ", map.score()));
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