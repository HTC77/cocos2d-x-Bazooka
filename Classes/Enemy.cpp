#include "Enemy.h"
#include "SimpleAudioEngine.h"

// on "init" you need to initialize your instance
bool Enemy::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Sprite::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();  

	float mrand = rand() % 3 + 1;
	float h = winSize.height * mrand * 0.25;
	this->initWithFile("bookGame_enemy.png");
	Vec2 p = Vec2(visibleSize.width + this->getContentSize().width / 2,
		h);
	this->setPosition(p);

    return true;
}

void Enemy::update()
{
	Vec2 _mp = this->getPosition();
	Vec2 _Mp = _mp + Vec2(-3, 0);
	this->setPosition(_Mp);
}

