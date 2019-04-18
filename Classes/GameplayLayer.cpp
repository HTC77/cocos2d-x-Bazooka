#include "GameplayLayer.h"
#include "SimpleAudioEngine.h"

GameplayLayer::GameplayLayer()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	winSize = Director::getInstance()->getWinSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

GameplayLayer::~GameplayLayer()
{

}

Vector<Enemy*>* GameplayLayer::getEnemiesArray()
{
	return &enemies;
}

Vector<Projectile*>* GameplayLayer::getEnemyBulletsArray()
{
	return &enemyBullets;
}

void GameplayLayer::update()
{
	// enemies
	if(enemies.size() > 0)
	{
		for (int i = 0; i < enemies.size(); ++i)
		{
			Enemy* e = enemies.at(i);
			e->update();
			if (e->getPositionX() + e->getContentSize().width / 2 < 0)
				enemiesToBeDeleted.pushBack(e);
		}
	}

	// enemy bullets
	if(enemyBullets.size() > 0)
	{
		for (int i = 0; i < enemyBullets.size(); ++i)
		{
			Projectile* pr = enemyBullets.at(i);
			pr->update();
			if (pr->getPositionX() <= 0)
				enemyBulletsToBeDeleted.pushBack(pr);
		}
	}

	Enemy* target = NULL;
	for (int i = 0; i < enemiesToBeDeleted.size(); ++i)
	{
		target = enemiesToBeDeleted.at(i);
		enemies.eraseObject(target);
		enemiesToBeDeleted.eraseObject(target);
		this->removeChild(target, true);
	}

	Projectile* targetP = NULL;
	for (int i = 0; i < enemyBulletsToBeDeleted.size(); ++i)
	{
		targetP = enemyBulletsToBeDeleted.at(i);
		enemyBullets.eraseObject(targetP);
		enemyBulletsToBeDeleted.eraseObject(targetP);
		this->removeChild(targetP, true);
	}
}

