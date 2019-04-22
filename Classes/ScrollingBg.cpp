#include "ScrollingBg.h"	

// on "init" you need to initialize your instance
bool ScrollingBg::init(string _name, float _speed, float _yPos)
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
	winSize = Director::getInstance()->getWinSize();
	speed = _speed;

	gameBg1 = Sprite::create(_name);
	gameBg1->setPosition(Vec2(winSize.width*0.5, _yPos));
	gameBg1->setAnchorPoint(Vec2(0.5,0.0));
	gameBg1->setScaleX(1.01);
	this->addChild(gameBg1);
	
	gameBg2 = Sprite::create(_name);
	gameBg2->setPosition(Vec2(winSize.width*0.5 + winSize.width, _yPos));
	gameBg2->setAnchorPoint(Vec2(0.5,0.0));
	gameBg2->setScaleX(1.01);
	this->addChild(gameBg2);

    return true;
}

void ScrollingBg::update()
{
	// scroll bg left or right
	Vec2 bg1pos = gameBg1->getPosition();
	gameBg1->setPosition(Vec2(bg1pos.x - speed, bg1pos.y));

	if (gameBg1->getPosition().x < -winSize.width / 2)
		gameBg1->setPosition(Vec2(winSize.width + winSize.width / 2,
			gameBg1->getPosition().y));

	Vec2 bg2pos = gameBg2->getPosition();
	gameBg2->setPosition(Vec2(bg2pos.x - speed, bg2pos.y));
	if (gameBg2->getPosition().x < -winSize.width / 2)
		gameBg2->setPosition(Vec2(winSize.width + winSize.width / 2,
			gameBg2->getPosition().y));
}

ScrollingBg* ScrollingBg::create(string _name, float _speed, float _yPos)
{
	ScrollingBg* obj = new ScrollingBg();
	if (obj && obj->init(_name, _speed, _yPos))
	{
		obj->autorelease();
		return obj;
	}
	CC_SAFE_DELETE(obj);
	return NULL;
}
