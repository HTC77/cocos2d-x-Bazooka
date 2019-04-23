#include "ParticleLayer.h"

ParticleLayer::ParticleLayer(Vec2 p)
{
	enemyDie = ParticleSpin::create(p, "EnemyDie.png");
	this->addChild(enemyDie);
	enemyGun = ParticleSpin::create(p, "EnemyGun.png");
	this->addChild(enemyGun);
	this->scheduleOnce(schedule_selector(ParticleLayer::removeSelf), 2.0);
	this->schedule(schedule_selector(ParticleLayer::update));
}

void ParticleLayer::removeSelf(float delta)
{
	this->unscheduleUpdate();
	this->removeFromParent();
}

void ParticleLayer::update(float delta)
{
	enemyDie->update(delta);
	enemyGun->update(delta);
}
