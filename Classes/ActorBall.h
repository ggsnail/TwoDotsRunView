#ifndef __ACTORBALL_H__
#define __ACTORBALL_H__

#include "cocos2d.h"
USING_NS_CC;

class ActorBall:public Sprite
{
public:
	
	Sprite* actorBallRed();
	Sprite* actorBallBlue();
	Vec2 rotateClock(Sprite* cenSpr, Sprite* arcSpr,float num);
	
protected:
private:
	float degree;
};


#endif //__ACTORBALL_H__