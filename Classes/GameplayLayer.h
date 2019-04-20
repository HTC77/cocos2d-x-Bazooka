#ifndef __BazookaGame_GameplayLayer__
#define __BazookaGame_GameplayLayer__

#include "cocos2d.h"
#include "Enemy.h"
#include "Projectile.h"
USING_NS_CC;

class GameplayLayer : public Layer
{
public:

	GameplayLayer(Sprite* _hero);
	~GameplayLayer();
    
    Size visibleSize;
    Size winSize;
    Vec2 origin;

	Vector<Enemy*> enemies;
	Vector<Enemy*> enemiesToBeDeleted;
	Vector<Enemy*>* getEnemiesArray();
	
	Vector<Projectile*> enemyBullets;
	Vector<Projectile*> enemyBulletsToBeDeleted;
	Vector<Projectile*>* getEnemyBulletsArray();

	Vector<Projectile*> playerBullets;
	Vector<Projectile*>* getPlayerBulletsArray();

	void update();

	bool checkBoxCollision(Sprite* box1, Sprite* box2);
	Sprite* hero;

	int score;
	bool gameOver;

};

#endif // __BazookaGame_GameplayLayer__
