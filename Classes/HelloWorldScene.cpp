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

	this->scheduleUpdate();

	// touch dispatcher
	EventListenerTouchOneByOne* touchListener =
		EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan =
		CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
		touchListener, this);

	// acceleration dispatcher
	Device::setAccelerometerEnabled(true); // enable accelerometer first
	EventListenerAcceleration* accelerateListener =
		EventListenerAcceleration::create(
			CC_CALLBACK_2(HelloWorld::accelerated,this));
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
		accelerateListener, this);

	// shoot button
	MenuItemImage* closeItem = MenuItemImage::create(
								"CloseNormal.png",
								"CloseSelected.png",
								 this,
								 menu_selector(HelloWorld::buttonControl)
								);
	closeItem->setPosition(Vec2(winSize.width * .125,
		winSize.height * .125));
	Menu* menu = Menu::create(closeItem, nullptr);
	menu->setPosition(Vec2());
	this->addChild(menu, 1);

	// enemy
	enemy = Enemy::create();
	this->addChild(enemy);

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
	float maxY = winSize.height - hero->getContentSize().height / 2;
	float minY = hero->getContentSize().height / 2;
	float distStep = (distFraction * delta);
	float newY = hero->getPosition().y + distStep;
	newY = MIN(MAX(newY, minY), maxY);
	hero->setPosition(ccp(hero->getPosition().x, newY));
	
	enemy->update();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 location =
		Director::getInstance()->convertToGL(touch->getLocationInView());
	CCMoveTo* moveAction = CCMoveTo::create(1, location);
	hero->runAction(EaseInOut::create(moveAction,1));
	CCLOG("Touch");
	return true;
}

void HelloWorld::accelerated(Acceleration* acceleration, Event* event)
{
	distFraction = visibleSize.height* acceleration->y;
}

void HelloWorld::buttonControl(Ref* sender)
{
	Sprite* test = Sprite::create("CloseNormal.png");
	test->setPosition(Vec2(
		hero->getPositionX() + hero->getContentSize().width / 2,
		hero->getPositionY()));
	test->setScale(0.5);
	this->addChild(test);
}
