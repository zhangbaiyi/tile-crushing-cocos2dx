

#ifndef __LEVEL_TRANS_SCENE_H__
#define __LEVEL_TRANS_SCENE_H__

#include "cocos2d.h"

class levelTrans : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void nextLevel(float dt);

};

#endif // __LEVEL_TRANS_SCENE_H__
