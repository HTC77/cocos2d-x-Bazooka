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

	// background
	Sprite* bg = Sprite::create("bookGame_Bg.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width * 0.5f,
		origin.y + visibleSize.height * 0.5f));
	this->addChild(bg);

	// hero
	hero = Sprite::create("bookGame_tinyBazooka.png");
	hero->setPosition(Vec2(winSize.width * 0.25, winSize.height * 0.5));
	this->addChild(hero, 5);

	// enable update
	this->scheduleUpdate();

	// touch dispatcher
	EventListenerTouchOneByOne* touchListener =
		EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan =
		CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
		touchListener, this);

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
		hudLayer->updateScore(gameplayLayer->score);

		gameplayLayer->update();

		if (jumping)
		{
			jumpTimer = 10;
			jumping = false;
		}
		if (jumpTimer > 0)
		{
			jumpTimer--;
			Vec2 p = hero->getPosition();
			Vec2 mP = p + Vec2(0, 7);
			hero->setPosition(mP);
		}
		else
		{
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
	Vec2 location =
		Director::getInstance()->convertToGL(touch->getLocationInView());
	if(!gameplayLayer->gameOver)
	{
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
	Vec2 p = hero->getPosition();
	p.x = p.x + hero->getContentSize().width;
	p.y = p.y - hero->getContentSize().height * 0.05;
	Projectile* rocket = Projectile::create(p, 2);
	gameplayLayer->addChild(rocket);
	gameplayLayer->getPlayerBulletsArray()->pushBack(rocket);
}

void HelloWorld::gameOver()
{
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
}
