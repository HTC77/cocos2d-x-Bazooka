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

void GameplayLayer::update()
{
	if(enemies.size() > 0)
	{
		for (int i = 0; i < enemies.size(); ++i)
		{
			Enemy* e = enemies.at(i);
			e->update();
			if (e->getPositionX() + e->getContentSize().width / 2 < 0)
			{
				enemiesToBeDeleted.pushBack(e);
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
}

