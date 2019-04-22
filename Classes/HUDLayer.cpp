#include "HUDLayer.h"
#include "SimpleAudioEngine.h"


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
