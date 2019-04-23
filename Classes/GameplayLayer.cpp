#include "GameplayLayer.h"
#include "SimpleAudioEngine.h"
#include "ParticleLayer.h"

GameplayLayer::GameplayLayer(Sprite* _hero)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	winSize = Director::getInstance()->getWinSize();
	origin = Director::getInstance()->getVisibleOrigin();
	hero = _hero;
	score = 0;
	gameOver = false;
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

Vector<Projectile*>* GameplayLayer::getPlayerBulletsArray()
{
	return &playerBullets;
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
			{
				gameOver = true;
				enemiesToBeDeleted.pushBack(e);
			}
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

	// player bullets and remove
	if(playerBullets.size() > 0)
	{
		for (int i = 0; i < playerBullets.size(); ++i)
		{
			Projectile* pr = playerBullets.at(i);
			pr->update();
			if (pr->getPositionX() >= winSize.width){
				playerBullets.eraseObject(pr);
				this->removeChild(pr, true);
			}
		}
	}

	//player rocket and enemies collision
	if (playerBullets.size() >= 0)
	{
		for (int i = 0; i < playerBullets.size(); ++i)
		{
			Projectile* p = playerBullets.at(i);
			if (enemies.size() > 0)
			{
				for (int j = 0; j < enemies.size(); ++j)
				{
					Enemy* en = enemies.at(j);
					if (checkBoxCollision(p,en))
					{
						score++;
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemyKill.wav");
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("rocketExplode.wav");

						// particles
						ParticleSystemQuad* smokeParticle =
							ParticleSystemQuad::create("smoke.plist");
						smokeParticle->setPosition(en->getPosition());
						this->addChild(smokeParticle);
						smokeParticle->setAutoRemoveOnFinish(true);
						ParticleSystemQuad* dustParticle =
							ParticleSystemQuad::create("dusts.plist");
						dustParticle->setPosition(en->getPosition());
						this->addChild(dustParticle);
						dustParticle->setAutoRemoveOnFinish(true);

						ParticleLayer* pLayer = new ParticleLayer(en->getPosition());
						this->addChild(pLayer);

						this->removeChild(p);
						playerBullets.eraseObject(p);
						enemiesToBeDeleted.pushBack(en);
						return; // to get out of the loop.
					}
				}
			}
		}
	}

	//enemy bullets and player
	if(enemyBullets.size() > 0)
	{
		for (int i = 0; i < enemyBullets.size(); ++i)
		{
			Projectile* pr = enemyBullets.at(i);
			if(checkBoxCollision(pr, hero))
			{
				enemyBulletsToBeDeleted.pushBack(pr);
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("playerKill.wav");
				gameOver = true;
			}
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
	
	// remove enemy bullets
	Projectile* targetP = NULL;
	for (int i = 0; i < enemyBulletsToBeDeleted.size(); ++i)
	{
		targetP = enemyBulletsToBeDeleted.at(i);
		enemyBullets.eraseObject(targetP);
		enemyBulletsToBeDeleted.eraseObject(targetP);
		this->removeChild(targetP, true);
	}
}

bool GameplayLayer::checkBoxCollision(Sprite* box1, Sprite* box2)
{
	Rect box1Rect = box1->getBoundingBox();
	Rect box2Rect = box2->getBoundingBox();
	
	if(box1Rect.intersectsRect(box2Rect))
		return true;
	
	return false;
}

