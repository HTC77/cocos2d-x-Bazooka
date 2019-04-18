#ifndef __BazookaGame_GameplayLayer__
#define __BazookaGame_GameplayLayer__

#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;

class GameplayLayer : public Layer
{
public:

	GameplayLayer();
	~GameplayLayer();
    
    Size visibleSize;
    Size winSize;
    Vec2 origin;

	Vector<Enemy*> enemies;
	Vector<Enemy*>* getEnemiesArray();

	Vector<Enemy*> enemiesToBeDeleted;

	void update();
};

#endif // __BazookaGame_GameplayLayer__
