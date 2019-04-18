#ifndef __BazookaGame_Projectile__
#define __BazookaGame_Projectile__

#include "cocos2d.h"
USING_NS_CC;

class Projectile : public Sprite
{
public:
    
    Size visibleSize;
    Size winSize;
    Vec2 origin;
	int type;

	static Projectile* create(Vec2 p, int _type);
    virtual bool init(Vec2 p, int _type);

	void update();
};

#endif // __BazookaGame_Projectile__
