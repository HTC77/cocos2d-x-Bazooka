#include "Enemy.h"
#include "SimpleAudioEngine.h"
#include "Projectile.h"
#include "GameplayLayer.h"

Enemy* Enemy::create(GameplayLayer* _gameplayLayer)
{
	Enemy* obj = new Enemy();
	if (obj && obj->init(_gameplayLayer))
	{
		obj->autorelease();
		return obj;
	}
	CC_SAFE_DELETE(obj);
	return nullptr;
}

// on "init" you need to initialize your instance
bool Enemy::init(GameplayLayer* _gameplayLayer)
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
	gameplayLayer = _gameplayLayer;

	float mrand = rand() % 3 + 1;
	float h = winSize.height * mrand * 0.25;
	this->initWithFile("bookGame_enemy.png");
	Vec2 p = Vec2(visibleSize.width + this->getContentSize().width / 2,
		h);
	this->setPosition(p);

	this->schedule(schedule_selector(Enemy::shoot), 1.3);

	//enemy animation
	SpriteBatchNode* spriteBatch =
		SpriteBatchNode::create("enemy_anim.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("enemy_anim.plist");
	this->createWithSpriteFrameName("enemy_idle_1.png");
	this->addChild(spriteBatch);
	
	Vector<SpriteFrame*> animFrames(4);
	char str1[100] = { 0 };
	for (int i = 1; i <= 4; ++i)
	{
		sprintf(str1, "enemy_idle_%d.png", i);
		SpriteFrame* frame = cache->spriteFrameByName(str1);
		animFrames.pushBack(frame);
	}
	Animation* idleAnimation =
		Animation::createWithSpriteFrames(animFrames, 0.25f);
	this->runAction(RepeatForever::create(Animate::create(idleAnimation)));

    return true;
}

void Enemy::shoot(float delta)
{
	Vec2 p = this->getPosition();
	p.x = p.x - this->getContentSize().width / 2;
	p.y = p.y - this->getContentSize().height * 0.05;
	Projectile* pr = Projectile::create(p, 1);
	gameplayLayer->addChild(pr);
	gameplayLayer->getEnemyBulletsArray()->pushBack(pr);
}

void Enemy::update()
{
	Vec2 _mp = this->getPosition();
	Vec2 _Mp = _mp + Vec2(-2, 0);
	this->setPosition(_Mp);
}

