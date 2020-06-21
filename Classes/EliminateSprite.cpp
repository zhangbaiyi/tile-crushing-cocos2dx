#include "EliminateSprite.h"

EliminateSprite*  EliminateSprite::create()
{
	EliminateSprite* spr = new EliminateSprite();
	spr->m_type = NORMAL_SPRITE;
	spr->m_imgIndex = rand() % TOTAL_SPRITE;
	spr->initWithSpriteFrameName(spriteNormal[spr->m_imgIndex]);
	spr->autorelease();
	return spr;
}