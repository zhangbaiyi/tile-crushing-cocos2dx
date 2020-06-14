#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class PauseScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	static cocos2d::Scene* PauseScene::createScene(RenderTexture* screenShot, bool isFlip);

	virtual bool init();

	CREATE_FUNC(PauseScene);
};

#endif