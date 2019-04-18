#ifndef __BazookaGame_Enemy__
#define __BazookaGame_Enemy__

#include "cocos2d.h"
class GameplayLayer;
USING_NS_CC;

class Enemy : public Sprite
{
public:

	static Enemy* create(GameplayLayer* _gameplayLayer);
    virtual bool init(GameplayLayer* _gameplayLayer);
    
    Size visibleSize;
    Size winSize;
    Vec2 origin;
	GameplayLayer* gameplayLayer;
	void shoot(float delta);
	void update();
};

#endif // __BazookaGame_Enemy__
