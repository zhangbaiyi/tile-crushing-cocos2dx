
#ifndef __RANK_H__
#define __RANK_H__

#include "cocos2d.h"

class rank : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(rank);
};

#endif // __RANK_H__
