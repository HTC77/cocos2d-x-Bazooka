#ifndef __BazookaGame_ParticleSpin__
#define __BazookaGame_ParticleSpin__

#include "cocos2d.h"
USING_NS_CC;

class ParticleSpin : public Sprite
{
public:
	ParticleSpin();
	~ParticleSpin();

	static ParticleSpin* create(Vec2 _cp, char* _fileName);
    virtual bool init();
	Vec2 speed, gravity;
	float spinCounter;
	void update(float delta) override;
};

#endif // __BazookaGame_ParticleSpin__
