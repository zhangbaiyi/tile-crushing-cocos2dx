#include "SpriteMap.h"
#include "GameDefine.h"
#include "GameArg.h"
#include "cocos2d.h"

USING_NS_CC;


void SpriteMap::add(int pos, EliminateSprite* ptr)
{
	map[pos] = ptr;
	normalMap[ptr->getImgIndex()] |= 1ULL << pos;
}

void SpriteMap::remove(int pos)
{
	normalMap[map[pos]->getImgIndex()] ^= 1ULL << pos;
	map[pos] = nullptr;
}

bool SpriteMap::actionJudge()
{
	if (!isAction)
		return false;

	for (const auto& i : map)
		if (i && i->getNumberOfRunningActions())
			return true;

	isAction = false;
	return false;
}

bool SpriteMap::check()
{
	unsigned long long needEliminate = eliminateMap();

	if (needEliminate)
	{
		eliminate(needEliminate);
		return true;
	}

	return false;
}

void SpriteMap::eliminate(unsigned long long need)
{
	isAction = true;
	int combo = 1;
	while (need)
	{
		int pos = msb(need);
		need ^= 1ULL << pos;
		EliminateSprite* p = map[pos];
		remove(pos);
		explode(p);
		combo++;
		total_score += 10 * combo;
		
	}
}



void SpriteMap::explode(EliminateSprite* p)
{
	p->runAction(cocos2d::Sequence::create(
		cocos2d::ScaleTo::create(0.2f, 0.0),
		cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Sprite::removeFromParent, p)),
		NULL));
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		float randomEffect = CCRANDOM_0_1();
		if (randomEffect < 0.3f)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Chomp.mp3",false);
			float volume = CocosDenshion::SimpleAudioEngine::getInstance()->getEffectsVolume();
			CCLOG("%f", volume);
		}
		else if (randomEffect >= 0.3f && randomEffect < 0.6f)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Scrape.mp3",false);
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Drip.mp3",false);
		}
	}
}

std::vector<int> SpriteMap::fill()
{
	std::vector<int> emptyRow(COLS, 0);
	for (int col = 0; col != COLS; ++col)
		for (int pos = col; pos < MAP_SIZE; pos += COLS)
		{
			if (map[pos] == nullptr)
				++emptyRow[col];
			else if (emptyRow[col] > 0)
			{
				auto p = map[pos];
				int newPos = pos - emptyRow[col] * COLS;

				add(newPos, p);
				remove(pos);

				cocos2d::Point endPosition = positionOfItem(newPos);
				float speed = (p->getPosition().y - endPosition.y) / GAME_SCREEN_HEIGHT * 3;
				p->stopAllActions();
				p->runAction(cocos2d::MoveTo::create(speed, endPosition));

			}
		}

	return emptyRow;
}

int SpriteMap::msb(unsigned long long arg)
{
	int retval = 0;
	if (arg & 0xffffffff00000000) { retval += 32; arg &= 0xffffffff00000000; }
	if (arg & 0xffff0000ffff0000) { retval += 16; arg &= 0xffff0000ffff0000; }
	if (arg & 0xff00ff00ff00ff00) { retval += 8; arg &= 0xff00ff00ff00ff00; }
	if (arg & 0xf0f0f0f0f0f0f0f0) { retval += 4; arg &= 0xf0f0f0f0f0f0f0f0; }
	if (arg & 0xcccccccccccccccc) { retval += 2; arg &= 0xcccccccccccccccc; }
	if (arg & 0xaaaaaaaaaaaaaaaa) { retval += 1; arg &= 0xaaaaaaaaaaaaaaaa; }
	return retval;
}

cocos2d::Point SpriteMap::positionOfItem(int pos)
{
	int row = pos / COLS;
	int col = pos % COLS;
	float x = mapLBX + (SPRITE_WIDTH + BOADER_WIDTH) * col + SPRITE_WIDTH / 2;
	float y = mapLBY + (SPRITE_WIDTH + BOADER_WIDTH) * row + SPRITE_WIDTH / 2;
	return cocos2d::Point(x, y);
}

bool SpriteMap::canTouch()
{
	return !isAction;
}

int  SpriteMap::spriteOfPoint(cocos2d::Point* point)
{
	cocos2d::Rect rect = cocos2d::Rect(0, 0, 0, 0);
	cocos2d::Size sz;
	sz.height = SPRITE_WIDTH;
	sz.width = SPRITE_WIDTH;
	rect.size = sz;

	for (int pos = 0; pos != MAP_SIZE; ++pos)
	{
		EliminateSprite* p = map[pos];
		if (p)
		{
			rect.origin.x = p->getPositionX() - (SPRITE_WIDTH / 2);
			rect.origin.y = p->getPositionY() - (SPRITE_WIDTH / 2);
			if (rect.containsPoint(*point))
				return pos;
		}
	}

	return -1;
}



void SpriteMap::swap(int staPosition, int endPosition)
{
	if (staPosition < 0 || endPosition < 0)
		return;

	int dis = std::abs(staPosition - endPosition);

	if (dis != 1 && dis != 8)
		return;
	isAction = true;

	float time = 0.2;
	auto staPtr = map[staPosition];
	auto endPtr = map[endPosition];
	auto toSta = cocos2d::MoveTo::create(time, staPtr->getPosition());
	auto toEnd = cocos2d::MoveTo::create(time, endPtr->getPosition());

	remove(staPosition);
	remove(endPosition);
	add(staPosition, endPtr);
	add(endPosition, staPtr);

	if (eliminateMap())
	{
		staPtr->runAction(toEnd->clone());
		endPtr->runAction(toSta->clone());

	}
	else
	{
		remove(staPosition);
		remove(endPosition);
		add(staPosition, staPtr);
		add(endPosition, endPtr);
		staPtr->runAction(cocos2d::Sequence::create(toEnd->clone(), toSta->clone(), nullptr));
		endPtr->runAction(cocos2d::Sequence::create(toSta->clone(), toEnd->clone(), nullptr));
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Error.mp3",false);
		}
	}
	
}

unsigned long long SpriteMap::eliminateMap()
{
	unsigned long long needEliminate = 0ULL;
	for (auto i : normalMap)
	{
		unsigned long long tmp = i;
		tmp &= tmp << COLS;
		tmp &= tmp >> COLS;
		tmp |= tmp << COLS;
		tmp |= tmp >> COLS;
		needEliminate |= tmp;

		tmp = i;
		tmp &= (tmp << 1) & 0xfefefefefefefefe;
		tmp &= (tmp >> 1) & 0x7f7f7f7f7f7f7f7f;
		tmp |= tmp << 1;
		tmp |= tmp >> 1;
		needEliminate |= tmp;
	}
	return needEliminate;
}