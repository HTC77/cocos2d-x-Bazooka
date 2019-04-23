#include "HUDLayer.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"


HUDLayer::HUDLayer()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	winSize = Director::getInstance()->getWinSize();
	origin = Director::getInstance()->getVisibleOrigin();
	scoreLabel = Label::createWithBMFont("PixelFont.fnt","Score: 0");
	scoreLabel->setPosition(Vec2(visibleSize.width * 0.5,
		visibleSize.height * 0.9));
	this->addChild(scoreLabel);
	scoreLabel->setScale(0.5);

	MenuItemImage* pauseItem =
		MenuItemImage::create("_bookgame_UI__pause.png",
							 "_bookgame_UI__pause.png",
							 this,
							 menu_selector(HUDLayer::pauseGame));
	pauseItem->setPosition(Vec2(visibleSize.width - pauseItem->getContentSize().width / 2,
								visibleSize.height - pauseItem->getContentSize().height / 2));
	pauseMenu = Menu::create(pauseItem,nullptr);
	pauseMenu->setPosition(Vec2());
	this->addChild(pauseMenu);
}

HUDLayer::~HUDLayer()
{
	
}

void HUDLayer::updateScore(int score)
{
	char scoreText[100];
	sprintf(scoreText, "Score: %d", score);
	scoreLabel->setString(scoreText);
}

void HUDLayer::pauseGame(Ref* sender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop.wav");
	HelloWorld* helloWorld = (HelloWorld*)this->getParent();
	if (!helloWorld->gameplayLayer->gameOver)
	{
		pauseMenu->setEnabled(false);

		MenuItemImage* resumeItem = MenuItemImage::create(
								"_bookgame_UI__resume.png",
								"_bookgame_UI__resume.png",
								this,
								menu_selector(HUDLayer::resumeGame));

		resumeItem->setPosition(Vec2(visibleSize.width * 0.5,visibleSize.height * 0.5));
		resumeMenu = Menu::create(resumeItem, nullptr);
		resumeMenu->setPosition(Vec2());
		this->addChild(resumeMenu);
		helloWorld->gamePaused();
	}
	CCLOG("PASUE CLICKED");
}

void HUDLayer::resumeGame(Ref* sender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop.wav");
	pauseMenu->setEnabled(true);
	this->removeChild(resumeMenu);
	HelloWorld* helloWorld = dynamic_cast<HelloWorld*>(getParent());
	helloWorld->gameResumed();
}
