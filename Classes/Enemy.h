#ifndef __BazookaGame_Enemy__
#define __BazookaGame_Enemy__

#include "cocos2d.h"
USING_NS_CC;

class Enemy : public Sprite
{
public:

    virtual bool init();
    
    Size visibleSize;
    Size winSize;
    Vec2 origin;

    // implement the "static create()" method manually
    CREATE_FUNC(Enemy);

	void update();
};

#endif // __BazookaGame_Enemy__
