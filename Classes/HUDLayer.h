#ifndef __BazookaGame_HUDLayer__
#define __BazookaGame_HUDLayer__

#include "cocos2d.h"
USING_NS_CC;

class HUDLayer : public Layer
{
public:  
	HUDLayer();
	~HUDLayer();

	Size visibleSize;
	Size winSize;
	Vec2 origin;
	Label* scoreLabel;
	void updateScore(int score);

	Menu* pauseMenu;
	Menu* resumeMenu;
	void pauseGame(Ref* sender);
	void resumeGame(Ref* sender);
	bool isPaused;
};

#endif // __BazookaGame_HUDLayer__
