
#ifndef __GAMEARG_H__
#define __GAMEARG_H__

#include "cocos2d.h"

static unsigned long long total_score;

class Score : public cocos2d::Layer {

public:
	Score();
	~Score();

	virtual bool init();
	void update(float dt);

	CREATE_FUNC(Score);


	
};





#endif // __GAMEARG_H__
