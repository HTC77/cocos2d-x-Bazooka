#ifndef __BazookaGame_OptionsMenuScene__
#define __BazookaGame_OptionsMenuScene___

#include "cocos2d.h"
#include "ScrollingBgLayer.h"
USING_NS_CC;

class OptionsMenu : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    Size visibleSize;
    Size winSize;
    Vec2 origin;

	ScrollingBgLayer* scrollingBgLayer;
	void reset(CCObject* pSender);
	void mainMenu(CCObject* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(OptionsMenu);
	void update(float delta) override;

	MenuItemImage* soundOnItem;
	MenuItemImage* soundOffItem;

	void soundOnOff(Ref* sender);
};

#endif // __BazookaGame_OptionsMenuScene___
