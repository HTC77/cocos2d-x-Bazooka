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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();

	// parallax  background
	scrollingBgLayer = new ScrollingBgLayer(3.0f);
	this->addChild(scrollingBgLayer);

	// hero
	hero = Sprite::create("bookGame_tinyBazooka.png");
	hero->setPosition(Vec2(winSize.width * 0.25, winSize.height * 0.5));
	this->addChild(hero, 5);

	//player animation
	SpriteBatchNode* spriteBatch =
		SpriteBatchNode::create("player_anim.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("player_anim.plist");
	hero->createWithSpriteFrameName("player_idle_1.png");
	hero->addChild(spriteBatch);

	//idle animation
	Vector<SpriteFrame*> animFrames(4);
	char str1[100] = { 0 };
	for (int i = 1; i <= 4; ++i)
	{
		sprintf(str1, "player_idle_%d.png", i);
		SpriteFrame* frame = cache->spriteFrameByName(str1);
		animFrames.pushBack(frame);
	}

	Animation* idleAnimation =
		Animation::createWithSpriteFrames(animFrames, 0.25f);
	mIdleAction = RepeatForever::create(Animate::create(idleAnimation));
	mIdleAction->retain();

	//boost animation
	animFrames.clear();
	char str2[100] = { 0 };
	for (int i = 1; i <= 4; i++)
	{
		sprintf(str2, "player_boost_%d.png", i);
		SpriteFrame* frame = cache->spriteFrameByName(str2);
		animFrames.pushBack(frame);
	}
	Animation* boostAnimation =
		Animation::createWithSpriteFrames(animFrames, 0.25f);
	mBoostAction = RepeatForever::create(Animate::create(boostAnimation));
	mBoostAction->retain();
	
	// enable update
	this->scheduleUpdate();

	// touch dispatcher
	touchListener =
		EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan =
		CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
		touchListener, this);
	touchListener->retain();

	// gameplay layer
	gameplayLayer = new GameplayLayer(hero);
	this->addChild(gameplayLayer);

	// spawn enemies
	this->schedule(schedule_selector(HelloWorld::spawnEnemy), 3.0f);

	// hero controls
	leftButton = Rect(0,0,visibleSize.width/2,visibleSize.height);
	rightButton = Rect(visibleSize.width / 2, 0, visibleSize.width / 2,
		visibleSize.height);
	gravity = Vec2(0, -5);
	jumping = false;
	jumpTimer = 0;

	// HudLayer
	hudLayer = new HUDLayer();
	this->addChild(hudLayer, 15); //keeping at top most layer

	// flameParticle: jet boost particle
	flameParticle = ParticleSystemQuad::create("jetBoost.plist");
	flameParticle->setPosition(hero->getPosition() +
							   Vec2(-hero->getContentSize().width * 0.25, 0));
	this->addChild(flameParticle);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void HelloWorld::update(float delta)
{
	if (!gameplayLayer->gameOver)
	{
		flameParticle->setPosition(hero->getPosition() +
			Vec2(-hero->getContentSize().width * 0.25, 0));

		this->AnimationStates();

		scrollingBgLayer->update();

		hudLayer->updateScore(gameplayLayer->score);

		gameplayLayer->update();

		if (jumping)
		{
			jumpTimer = 10;
			jumping = false;
		}
		if (jumpTimer > 0)
		{
			mPlayerState = kPlayerStateBoost;
			jumpTimer--;
			Vec2 p = hero->getPosition();
			Vec2 mP = p + Vec2(0, 7);
			hero->setPosition(mP);
		}
		else
		{
			mPlayerState = kPLayerStateIdle;
			jumpTimer = 0;
			Vec2 p = hero->getPosition();
			Vec2 pM = p + gravity;
			hero->setPosition(pM);
		}
		float maxY = visibleSize.height - hero->getContentSize().height / 2;
		float minY = hero->getContentSize().height / 2;
		float newY = hero->getPosition().y;
		newY = MIN(MAX(newY, minY), maxY);
		hero->setPosition(Vec2(hero->getPosition().x, newY));
	}else
	{
		gameOver();
	}
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	if(!gameplayLayer->gameOver)
	{
		Vec2 location =
			Director::getInstance()->convertToGL(touch->getLocationInView());
		if (rightButton.containsPoint(location))
			fireRocket();
		if (leftButton.containsPoint(location))
			jumping = true;
	}
	return true;
}


void HelloWorld::spawnEnemy(float dt)
{
	Enemy* e = Enemy::create(gameplayLayer);
	gameplayLayer->addChild(e);
	e->shoot(0.016); // first shoot
	gameplayLayer->getEnemiesArray()->pushBack(e);
}

void HelloWorld::fireRocket()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fireRocket.wav");
	// particle system
	m_emitter = ParticleExplosion::create();
	m_emitter->setPosition(hero->getPosition() +
	Vec2(hero->getContentSize().width / 2, 0));
	m_emitter->setStartColor(Color4F(1.0, 1.0, 1.0, 1.0));
	m_emitter->setEndColor(Color4F(0.0, 0.0, 0.0, 0.0));
	m_emitter->setTotalParticles(1000);
	m_emitter->setLife(0.25);
	m_emitter->setSpeed(2.0);
	m_emitter->setSpeedVar(30.0);

	//** gravity
	m_emitter->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	m_emitter->setGravity(Vec2(0, 90));

	//** mode radius
	m_emitter->setEmitterMode(ParticleSystem::Mode::RADIUS);
	m_emitter->setStartRadius(0);
	m_emitter->setStartRadiusVar(50);
	m_emitter->setRotatePerSecond(2);
	m_emitter->setRotatePerSecondVar(5);

	this->addChild(m_emitter);
	
	Vec2 p = hero->getPosition();
	p.x = p.x + hero->getContentSize().width;
	p.y = p.y - hero->getContentSize().height * 0.05;
	Projectile* rocket = Projectile::create(p, 2);
	gameplayLayer->addChild(rocket);
	gameplayLayer->getPlayerBulletsArray()->pushBack(rocket);
}

void HelloWorld::gameOver()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop.wav");
	this->unscheduleAllSelectors();
	if(gameplayLayer->getEnemiesArray()->size() > 0)
	{
		for (int i = 0; i < gameplayLayer->getEnemiesArray()->size(); ++i)
		{
			Enemy* en = gameplayLayer->getEnemiesArray()->at(i);
			en->unscheduleAllSelectors();
		}
	}
	Label* gameOverLabel =
		Label::createWithBMFont("PixelFont.fnt", "GAMEOVER");
	gameOverLabel->setPosition(Vec2(visibleSize.width * 0.5,
		visibleSize.height * 0.6));
	this->addChild(gameOverLabel, 10);

	// high score
	int highScore = UserDefault::getInstance()->getIntegerForKey("bazookaGameHighScore");

	if (gameplayLayer->score > highScore){
		UserDefault::getInstance()->setIntegerForKey("bazookaGameHighScore", gameplayLayer->score);
		Label* newHighScoreLabel = Label::createWithBMFont("PixelFont.fnt", "NEW HIGH SCORE");
		newHighScoreLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
		this->addChild(newHighScoreLabel, 10);
		newHighScoreLabel->setScale(0.75f);
		Label* newScoreLabel = Label::createWithBMFont("PixelFont.fnt",
			StringUtils::format("%d", gameplayLayer->score));
		newScoreLabel->setPosition(Vec2(visibleSize.width * 0.5,
			visibleSize.height * 0.4));
		this->addChild(newScoreLabel, 10);
	}else{
		Label* newHighScoreLabel = Label::createWithBMFont("PixelFont.fnt", "BETTER LUCK NEXT TIME");
		newHighScoreLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
		this->addChild(newHighScoreLabel, 10);
		newHighScoreLabel->setScale(0.75f);
	}

	MenuItemImage* mainmenuItem = MenuItemImage::create(
		"_bookgame_UI_mainmenu.png",
		"_bookgame_UI_mainmenu.png", this,
		menu_selector(HelloWorld::mainMenuScene));
	mainmenuItem->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height * 0.2));
	Menu* mainMenu = Menu::create(mainmenuItem,NULL);
	mainMenu->setPosition(Point());
	this->addChild(mainMenu);
}

void HelloWorld::gamePaused()
{
	this->unscheduleUpdate();
	this->unschedule(schedule_selector(HelloWorld::spawnEnemy));	
	this->getEventDispatcher()->removeEventListener(touchListener);

	if (gameplayLayer->getEnemiesArray()->size() > 0)
	{
		for (int i = 0; i < gameplayLayer->getEnemiesArray()->size(); ++i)
		{
			Enemy* en = gameplayLayer->getEnemiesArray()->at(i);
			en->pauseSchedulerAndActions();
		}
	}
}

void HelloWorld::gameResumed()
{
	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::spawnEnemy), 3.0f);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
		touchListener, this);

	if (gameplayLayer->getEnemiesArray()->size() > 0)
	{
		for (int i = 0; i < gameplayLayer->getEnemiesArray()->size(); ++i)
		{
			Enemy* en = gameplayLayer->getEnemiesArray()->at(i);
			en->resumeSchedulerAndActions();
		}
	}
}


void HelloWorld::AnimationStates()
{
	switch (mPlayerState)
	{
	case kPLayerStateIdle:
		this->idleAnim(); break;
	case kPlayerStateBoost:
		this->boostAnim(); break;
	default: break;
	}
}

void HelloWorld::mainMenuScene(Ref* sender)
{
	Director::getInstance()->replaceScene(MainMenu::createScene());
}

void HelloWorld::idleAnim()
{
	if (mActionState != kActionStateIdle)
	{
		hero->stopAllActions();
		hero->runAction(mIdleAction);
		mActionState = kActionStateIdle;
	}
}

void HelloWorld::boostAnim()
{
	if (mActionState != kActionStateBoost)
	{
		hero->stopAllActions();
		hero->runAction(mBoostAction);
		mActionState = kActionStateBoost;
	}
}