#include "GameScene.h"
#include "PauseScene.h"
#include "EliminateSprite.h"
#include "GameDefine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

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
	MenuItemImage *pPauseItem = MenuItemImage::create("buttons/pause.png", "buttons/pause_clicked.png",
	[&](Ref* sender)
	{
			GameScene::menuPauseCallback(sender);
	});
	pPauseItem->setPosition(Vec2(GAME_SCREEN_WIDTH - pPauseItem->getContentSize().width / 2,
		pPauseItem->getContentSize().height / 2));

	MenuItems.pushBack(pPauseItem);


	auto menu = Menu::createWithArray(MenuItems);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto labelScore = Score::create();
	this->addChild(labelScore);

	initMap();
	scheduleUpdate();

	return true;
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

void GameScene::menuPauseCallback(Ref* pSender)
{
	RenderTexture* renderTexture = RenderTexture::create(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);

	renderTexture->begin();
	this->visit();
	renderTexture->end();

	Director::getInstance()->pushScene(PauseScene::scene(renderTexture));
}