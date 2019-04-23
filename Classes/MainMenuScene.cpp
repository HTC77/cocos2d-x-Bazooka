#include "MainMenuScene.h"
#include "HelloWorldScene.h"

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

// on "init" you need to initialize your instance
bool MainMenu::init()
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
	scrollingBgLayer = new ScrollingBgLayer(3.0);
	this->addChild(scrollingBgLayer);
	Label* nameLabel =
		Label::createWithBMFont("PixelFont.fnt", "Ms.tinyBazooka");
	nameLabel->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height * 0.8));
	this->addChild(nameLabel);

	//actions
	MoveTo* actionMove = MoveTo::create(1, Vec2(nameLabel->getPosition().x,
		nameLabel->getPosition().y + 20));
	CallFuncN* actionMoveDone =
	 	CallFuncN::create(CC_CALLBACK_1(MainMenu::MoveUpFinished,this));
	EaseInOut* easeInOut = EaseInOut::create(actionMove,1);
	nameLabel->runAction(Sequence::create(easeInOut, actionMoveDone,NULL));

	skeletonNode = spine::SkeletonAnimation::createWithJsonFile(
		"player.json", "player.atlas", 1.0f);
	skeletonNode->addAnimation(0, "runCycle", true, 0);
	skeletonNode->setPosition(Vec2(visibleSize.width / 2,
		skeletonNode->getContentSize().height / 2));
	this->addChild(skeletonNode);

	MenuItemImage* playItem =
		MenuItemImage::create("_bookgame_UI_play.png", "_bookgame_UI_play.png",
			this, menu_selector(MainMenu::playGame));
	playItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.5));
	MenuItemImage* optionsItem =
		MenuItemImage::create("_bookgame_UI_options.png", "_bookgame_UI_options.png",
			this, menu_selector(MainMenu::optionsScene));
	optionsItem->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.5));
	//create menu, it's an autorelease object
	Menu* menu = Menu::create(optionsItem, playItem, NULL);
	menu->setPosition(Point());
	this->addChild(menu, 10);

	Label* newHighScoreLabel =
		Label::createWithBMFont("PixelFont.fnt","CURRENT HIGH SCORE");
	newHighScoreLabel->setPosition(Vec2(visibleSize.width * 0.5,
		visibleSize.height * 0.15));
	this->addChild(newHighScoreLabel, 10);
	newHighScoreLabel->setScale(0.5);

	Label* highScoreLabel = Label::createWithBMFont("PixelFont.fnt",
		StringUtils::format("%d",
			UserDefault::getInstance()->getIntegerForKey("bazookaGameHighScore")));
	highScoreLabel->setPosition(Vec2(visibleSize.width * 0.5,
		visibleSize.height * 0.08));
	this->addChild(highScoreLabel, 10);
	highScoreLabel->setScale(0.5);

	this->scheduleUpdate();

    return true;
}

void MainMenu::optionsScene(Ref* pSender)
{
	//code to replace Options scene
}

void MainMenu::playGame(Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void MainMenu::update(float delta)
{
	scrollingBgLayer->update();
}

void MainMenu::MoveDownFinished(Ref* sender)
{
	Label* sprite = dynamic_cast<Label*>(sender);
	MoveTo* actionMove = MoveTo::create(1.0,
		Vec2(sprite->getPosition().x, sprite->getPosition().y + 20));
	CallFuncN* actionMoveDone =
		CallFuncN::create(CC_CALLBACK_1(MainMenu::MoveUpFinished, this));
	EaseInOut* easeInOut = EaseInOut::create(actionMove, 1);
	sprite->runAction(Sequence::create(easeInOut, actionMoveDone, NULL));
}

void MainMenu::MoveUpFinished(Ref* sender)
{
	 Label* sprite = dynamic_cast<Label*>(sender);
	 MoveTo* actionMove = MoveTo::create(1.0,
	 	Vec2(sprite->getPosition().x, sprite->getPosition().y - 20));
	 CallFuncN* actionMoveDone =
	 	CallFuncN::create(CC_CALLBACK_1(MainMenu::MoveDownFinished, this));
	 EaseInOut* easeInOut = EaseInOut::create(actionMove, 1);
	 sprite->runAction(Sequence::create(easeInOut, actionMoveDone, NULL));
}

