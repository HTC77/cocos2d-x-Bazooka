#include "Projectile.h"
#include "SimpleAudioEngine.h"


Projectile* Projectile::create(Vec2 p, int _type)
{
	Projectile* obj = new Projectile();
	if(obj && obj->init(p, _type))
	{
		obj->autorelease();
		return obj;
	}
	CC_SAFE_DELETE(obj);
	return nullptr;
}

// on "init" you need to initialize your instance
bool Projectile::init(Vec2 p, int _type)
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
	type = _type;
	
	if (type == 1)
		this->initWithFile("bookGame_bullet.png");
	else if(type == 2)
		this->initWithFile("bookGame_rocket.png");

	this->setPosition(p);

    return true;
}

void Projectile::update()
{
	if(type ==1 )
	{
		Vec2 _mp = this->getPosition();
		Vec2 _Mp = _mp + Vec2(-7, 0);
		this->setPosition(_Mp);
	}else if (type == 2)
	{
		Vec2 _mp = this->getPosition();
		Vec2 _Mp = _mp + Vec2(+7, 0);
		this->setPosition(_Mp);
	}
}

