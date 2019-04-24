#include "OptionsMenuScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

Scene* OptionsMenu::createScene()
{
    return OptionsMenu::create();
}

// on "init" you need to initialize your instance
bool OptionsMenu::init()
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
		Label::createWithBMFont("PixelFont.fnt", "Options Menu");
	nameLabel->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height * 0.8));
	this->addChild(nameLabel);

	MenuItemImage* resetItem =
		MenuItemImage::create("_bookgame_UI__resume.png", "_bookgame_UI__resume.png",
			this, menu_selector(OptionsMenu::reset));
	resetItem->setPosition(Vec2(visibleSize.width * 0.5 - visibleSize.width *
		0.125, visibleSize.height * 0.5));

	MenuItemImage* mainMenuItem =
			MenuItemImage::create("_bookgame_UI_mainmenu.png", "_bookgame_UI_mainmenu.png",
				this, menu_selector(OptionsMenu::mainMenu));

	mainMenuItem->setPosition(Vec2(visibleSize.width * 0.5 + visibleSize.width
		* 0.125, visibleSize.height * 0.5));

	Menu* menu = Menu::create(mainMenuItem, resetItem, NULL);
	menu->setPosition(Point());
	this->addChild(menu, 10);

	this->scheduleUpdate();

	//sound onoff items
	soundOnItem = MenuItemImage::create(
		"_bookgame_UI_soundON.png", "_bookgame_UI_soundON.png", this, NULL);
	soundOffItem = MenuItemImage::create(
	"_bookgame_UI_soundOFF.png", "_bookgame_UI_soundOFF.png", this, NULL);

	bool isPaused = UserDefault::getInstance()->getBoolForKey("tinyBazooka_kSoundPausedKey");

	MenuItemToggle* soundToggleItem;
	if(isPaused == false)
	{
		soundToggleItem = MenuItemToggle::createWithTarget(this,
			menu_selector(OptionsMenu::soundOnOff),
			soundOnItem,
			soundOffItem, NULL);
	}else
	{
		soundToggleItem = MenuItemToggle::createWithTarget(this,
			menu_selector(OptionsMenu::soundOnOff),
			soundOffItem,
			soundOnItem , NULL);
	}

	soundToggleItem->setPosition(Vec2(visibleSize.width* 0.5,
		visibleSize.height * 0.5));

	menu->addChild(soundToggleItem);

    return true;
}

void OptionsMenu::reset(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop.wav");
	UserDefault::getInstance()->setIntegerForKey("bazookaGameHighScore", 0);
	UserDefault::getInstance()->flush();
}

void OptionsMenu::mainMenu(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop.wav");
	Scene* scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

void OptionsMenu::update(float delta)
{
	scrollingBgLayer->update();
}

void OptionsMenu::soundOnOff(Ref* sender)
{
	MenuItemToggle* toggleItem = dynamic_cast<MenuItemToggle*>(sender);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pop.wav");
	if (toggleItem->getSelectedItem() == soundOffItem)
	{
		UserDefault::getInstance()->setBoolForKey("tinyBazooka_kSoundPausedKey",
			true);
		UserDefault::getInstance()->flush();
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}else if (toggleItem->getSelectedItem() == soundOnItem)
	{
		UserDefault::getInstance()->setBoolForKey("tinyBazooka_kSoundPausedKey",
			false);
		UserDefault::getInstance()->flush();
		if(CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		else
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgMusic.wav");
	}
}

