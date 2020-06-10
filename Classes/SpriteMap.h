#ifndef __Sprite_MAP_H__
#define __Sprite_MAP_H__

#include "EliminateSprite.h"
#include <vector>

class SpriteMap
{
private:
	std::vector<EliminateSprite*> map = std::vector<EliminateSprite*>(MAP_SIZE, nullptr);
	std::vector<unsigned long long> normalMap = std::vector<unsigned long long>(TOTAL_SPRITE, 0ULL);
	bool isAction = true;
	int msb(unsigned long long);
	float mapLBX = (GAME_SCREEN_WIDTH - SPRITE_WIDTH * COLS - (COLS - 1) * BOADER_WIDTH) / 2;
	float mapLBY = (GAME_SCREEN_HEIGHT - SPRITE_WIDTH * ROWS - (ROWS - 1) * BOADER_WIDTH) / 2;
public:
	void add(int pos, EliminateSprite* ptr);
	void remove(int pos);
	cocos2d::Point positionOfItem(int pos);
	bool actionJudge();
	bool check();
	void eliminate(unsigned long long);
	void explode(EliminateSprite*);
	std::vector<int> fill();
};

#endif