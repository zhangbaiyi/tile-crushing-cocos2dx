#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SpriteMap.h"


USING_NS_CC;

class GameScene : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();

	void initMap();

	void createSprite(int pos);

	void update(float t);

	void checkSprite();

	bool onTouchBegan(Touch* touch, Event* unused);
	void onTouchMoved(Touch* touch, Event* unused);

	void controllerCreate(int);
	void timeUpdate(float);


	CREATE_FUNC(GameScene);
private:
	SpriteBatchNode* spriteSheet;

	SpriteMap map;

	const int* limit;

	int staPosition = -1;
};

#endif