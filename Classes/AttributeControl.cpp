#include <AttributeControl.h>
#include <sstream>

const int* AttributeControl::create(int mod)
{
	myModel = mod;
	if (myModel == ZEN_MODEL)
	{
		myAim = cocos2d::UserDefault::getInstance()->getIntegerForKey("Zen");
		if (!myAim)
			cocos2d::UserDefault::getInstance()->setIntegerForKey("Zen", 0);
		return &zen;
	}
	if (myModel == GENERAL_MODEL)
	{
		myAim = cocos2d::UserDefault::getInstance()->getIntegerForKey("General");
		if (!myAim)
			cocos2d::UserDefault::getInstance()->setIntegerForKey("Genenral", 0);
		return &time;
	}
	if (myModel == RLIKE_MODEL)
	{
		myAim = level * SCORE_PER_LEVEL;
		step = LEVEL_TO_STEP(level);
		return &step;
	}
	if (myModel == CONTINUE_MODEL)
	{
		level = cocos2d::UserDefault::getInstance()->getIntegerForKey("Level");
		if (!level)
		{
			cocos2d::UserDefault::getInstance()->setIntegerForKey("Level", 1);
			level = 1;
		}
		myAim = level * SCORE_PER_LEVEL;
		step = LEVEL_TO_STEP(level);
		for (int i = 0; i != TOTAL_SPRITE; ++i)
		{
			std::ostringstream buffer;
			buffer << "Score" << i;
			int multiple = cocos2d::UserDefault::getInstance()->getIntegerForKey(buffer.str().c_str());
			if (!multiple)
			{
				cocos2d::UserDefault::getInstance()->setIntegerForKey(buffer.str().c_str(), 1);
				multiple = 1;
			}
			scores[i] = multiple * BASE_SCORE;
		}
	}
}

const char* AttributeControl::getLimitType()
{
	return limitType.c_str();
}

void AttributeControl::timeUpdate()
{
	--time;
}

void AttributeControl::stepUpdate()
{
	--step;
}

int AttributeControl::aim()
{
	return myAim;
}

int AttributeControl::model()
{
	return myModel;
}

int AttributeControl::getScore(int n)
{
	return scores[n];
}