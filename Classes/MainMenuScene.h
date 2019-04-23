#ifndef __BazookaGame_MainMenuScene__
#define __BazookaGame_MainMenuScene__

#include "cocos2d.h"
#include "ScrollingBgLayer.h"
#include "spine/SkeletonAnimation.h"
USING_NS_CC;

class MainMenu : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
	ScrollingBgLayer* scrollingBgLayer;
	void optionsScene(Ref* pSender);
	void playGame(Ref* pSender);
	void update(float delta) override;

    Size visibleSize;
    Size winSize;
    Vec2 origin;

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);

	void MoveDownFinished(Ref* sender);
	void MoveUpFinished(Ref* sender);
	spine::SkeletonAnimation* skeletonNode;
};

#endif // __BazookaGame_MainMenuScene__
