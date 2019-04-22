#ifndef __BazookaGame_ScrollingBgLayer__
#define __BazookaGame_ScrollingBgLayer__

#include "cocos2d.h"
#include "ScrollingBg.h"
USING_NS_CC;

class ScrollingBgLayer : public Layer
{
public:
	ScrollingBgLayer(float _speed);
	~ScrollingBgLayer() = default;
    
	Size visibleSize;

	ScrollingBg* hills;
	ScrollingBg* treesNbush;
	ScrollingBg* ground;
	ScrollingBg* grass;
	
	void update();

};

#endif // __BazookaGame_ScrollingBgLayer__
