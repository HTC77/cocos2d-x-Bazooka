#include "OptionsMenuScene.h"
#include "MainMenuScene.h"

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

    return true;
}

void OptionsMenu::reset(CCObject* pSender)
{
	UserDefault::getInstance()->setIntegerForKey("bazookaGameHighScore", 0);
	UserDefault::getInstance()->flush();
}

void OptionsMenu::mainMenu(CCObject* pSender)
{
	Scene* scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

void OptionsMenu::update(float delta)
{
	scrollingBgLayer->update();
}

