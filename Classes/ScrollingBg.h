#ifndef __BazookaGame_ScrollingBg__
#define __BazookaGame_ScrollingBg__

#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class ScrollingBg : public Node
{
public:
    static ScrollingBg* create(string _name,float _speed, float _yPos);
    virtual bool init(string _name, float _speed, float _yPos);
	
	Sprite* gameBg1, *gameBg2;
	float speed;
	string name;
    Size winSize;

	void update();
};

#endif // __BazookaGame_ScrollingBg__
