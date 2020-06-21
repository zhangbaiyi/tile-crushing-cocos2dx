#ifndef __Attribute_CONTROL_H__
#define __Attribute_CONTROL_H__

#include <string>
#include <vector>
#include <GameDefine.h>
#include "cocos2d.h"

class AttributeControl
{
public:
	const int* create(int);
	const char* getLimitType();
	void timeUpdate();
	void stepUpdate();
	int aim();
	int model();
	int getScore(int);
private:
	int time = 60;
	int step = 5;
	int zen = 999;
	int myAim;
	int level = 1;
	int myModel;
	std::string limitType = "Time";
	std::vector<int> scores = std::vector<int>(TOTAL_SPRITE, BASE_SCORE);
};

#endif