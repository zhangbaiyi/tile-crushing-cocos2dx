#ifndef __ELIMINATE_SPRITE_H__
#define __ELIMINATE_SPRITE_H__

#include "cocos2d.h"
#include "GameDefine.h"


class EliminateSprite : public cocos2d::Sprite
{
public:
	static EliminateSprite* create();

	CC_SYNTHESIZE(int, m_imgIndex, ImgIndex);
	CC_SYNTHESIZE(int, m_type, Type);
};

#endif