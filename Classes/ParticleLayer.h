#ifndef __BazookaGame_ParticleLayer__
#define __BazookaGame_ParticleLayer__

#include "cocos2d.h"
#include "ParticleSpin.h"
USING_NS_CC;

class ParticleLayer : public Layer
{
public:
	ParticleLayer(Vec2 p);
	ParticleSpin* enemyDie;
	ParticleSpin* enemyGun;
	void removeSelf(float delta);
	void update(float delta);
};

#endif // __BazookaGame_ParticleLayer__
