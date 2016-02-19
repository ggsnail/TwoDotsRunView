#include "ActorBall.h"
#include "cocos2d.h"
USING_NS_CC;

#define PI 3.1415926
//#define CCRANDOM_0_1() ((float)rand()/RAND_MAX)

Sprite* ActorBall::actorBallBlue()
{
	auto actor = Sprite::createWithSpriteFrameName("small_1.png");
	actor->setTag(100);
	return actor;
}

Sprite* ActorBall::actorBallRed()
{
	auto actor = Sprite::createWithSpriteFrameName("small_2.png");
	actor->setTag(100);
	return actor;
}

Vec2 ActorBall::rotateClock(Sprite* cenSpr, Sprite* arcSpr,float num) //顺时针旋转,float num代表方向，+为逆，-为顺。
{
	Vec2 cenP = cenSpr->getPosition();//圆心的精灵
	Vec2 arcP = arcSpr->getPosition();//公转的精灵
	degree = atan2((cenP.y - arcP.y), (cenP.x - arcP.x));// 计算两精灵之间的角度
	degree = degree -num;
	auto newX = cenP.x - 64 * cos(degree);
	auto newY = cenP.y - 64 * sin(degree);
	auto newPosition = Vec2(newX, newY);
	return newPosition;
}
