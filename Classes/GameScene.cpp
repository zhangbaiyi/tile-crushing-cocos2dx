#include "GameScene.h"
#include "PauseScene.h"
#include "EliminateSprite.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
		return false;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon.plist");
	spriteSheet = SpriteBatchNode::create("icon.png");
	addChild(spriteSheet, 0);

	auto sprite = Sprite::create("scene_bg.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite, -1);

	auto pauseItem = MenuItemImage::create("btn_back01.png", "btn_back02.png",
		[&](Ref* sender)
	{
		auto scene = PauseScene::createScene();
		Director::getInstance()->pushScene(scene);
	});
	pauseItem->setPosition(Vec2(GAME_SCREEN_WIDTH - pauseItem->getContentSize().width / 2, 
		pauseItem->getContentSize().height / 2));

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

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