/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "GameplayLayer.h"
#include "HUDLayer.h"
#include "ScrollingBgLayer.h"
#include "spine/SkeletonAnimation.h"
USING_NS_CC;

typedef enum ActionState
{
	kActionStateNone = 0,
	kActionStateIdle,
	kActionStateBoost
};
typedef enum PlayerState
{
	kPlayerStateNone = 0,
	kPLayerStateIdle,
	kPlayerStateBoost
};

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	Size visibleSize, winSize;
	Vec2 origin;
	Sprite* hero;
	void update(float delta) override;

	EventListenerTouchOneByOne* touchListener;
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCanceled(Touch* touch, Event* event);


	GameplayLayer* gameplayLayer;

	void spawnEnemy(float dt);
	void fireRocket();

	Rect leftButton, rightButton;
	Vec2 gravity;
	int jumpTimer;
	bool jumping;

	void gameOver();

	HUDLayer* hudLayer;

	void gamePaused();
	void gameResumed();
	ScrollingBgLayer* scrollingBgLayer;

	ActionState mActionState;
	PlayerState mPlayerState;

	Action* mIdleAction;
	Action* mBoostAction;

	void idleAnim();
	void boostAnim();
	void AnimationStates();

	ParticleSystemQuad* m_emitter;
	ParticleSystemQuad* flameParticle;
};

#endif // __HELLOWORLD_SCENE_H__
