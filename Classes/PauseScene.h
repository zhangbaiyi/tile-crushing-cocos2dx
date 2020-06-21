#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class PauseScene : public cocos2d::Layer
{
public:
	
	virtual bool init() ;
	static cocos2d::Scene* scene(RenderTexture* screenShot);

	

	CREATE_FUNC(PauseScene);


};




#endif