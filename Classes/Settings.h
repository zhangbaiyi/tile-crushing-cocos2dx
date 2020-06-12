#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "cocos2d.h"

class Settings : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Settings);
};

#endif