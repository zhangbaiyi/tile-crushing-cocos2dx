
#include "GameArg.h"
#include "GameDefine.h"

USING_NS_CC;

Score::Score()
{
}


Score::~Score()
{
}

bool Score::init()
{
	if (!Layer::init())
	{
		return false;
	}

	
	auto labelScore = Label::createWithTTF(std::to_string(total_score), "fonts/Marker Felt.ttf", 30);
	
	labelScore->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT - labelScore->getContentSize().height * 2.6));
	labelScore->setTextColor(Color4B::YELLOW);
	labelScore -> setTag(10);
	this->addChild(labelScore);

	scheduleUpdate();
	
	return true;
}


void Score::update(float dt)
{ 
	cocos2d::Label* labelScore = (cocos2d::Label*)this->getChildByTag(10);
	labelScore->setString(std::to_string(total_score));
}
