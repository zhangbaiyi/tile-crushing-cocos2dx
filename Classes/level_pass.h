

#ifndef __LEVEL_PASS_SCENE_H__
#define __LEVEL_PASS_SCENE_H__

#include "cocos2d.h"

class levelPass : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

};

#endif // __LEVEL_PASS_SCENE_H__
