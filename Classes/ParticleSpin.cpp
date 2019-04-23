#include "ParticleSpin.h"


ParticleSpin::ParticleSpin()
{
	spinCounter = 0;
}

ParticleSpin::~ParticleSpin()
{
}

ParticleSpin* ParticleSpin::create(Vec2 _cp, char* _fileName)
{
	ParticleSpin *pc = new ParticleSpin();
	if (pc && pc->initWithFile(_fileName))
	{
		pc->setPosition(_cp);
		pc->init();
		pc->autorelease();
		return pc;
	}
	CC_SAFE_DELETE(pc);
	return NULL;
}

// on "init" you need to initialize your instance
bool ParticleSpin::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
	gravity = Vec2(0, -0.25);
	speed.x = CCRANDOM_MINUS1_1() * 2.0f;
	speed.y = rand() % 3 + 1;

    return true;
}

void ParticleSpin::update(float delta)
{
	spinCounter += delta * 4;
	Vec2 initpos = this->getPosition();
	Vec2 finalpos;
	finalpos.x = initpos.x + speed.x;
	speed.y += gravity.y;
	finalpos.y = initpos.y + speed.y + gravity.y;
	this->setPosition(finalpos);
	this->setRotation(CC_RADIANS_TO_DEGREES(spinCounter * speed.x));
}

