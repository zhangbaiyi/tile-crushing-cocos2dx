#ifndef __TRANSFER_SCENE_H__
#define __TRANSFER_SCENE_H__

#include "cocos2d.h"

class TransferScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TransferScene);

	void nextCallBack(Ref* pSender);
	void returnToStartCallBack(Ref* pSender);
};

#endif
