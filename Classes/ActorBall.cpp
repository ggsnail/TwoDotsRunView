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

Vec2 ActorBall::rotateClock(Sprite* cenSpr, Sprite* arcSpr,float num) //˳ʱ����ת,float num������+Ϊ�棬-Ϊ˳��
{
	Vec2 cenP = cenSpr->getPosition();//Բ�ĵľ���
	Vec2 arcP = arcSpr->getPosition();//��ת�ľ���
	degree = atan2((cenP.y - arcP.y), (cenP.x - arcP.x));// ����������֮��ĽǶ�
	degree = degree -num;
	auto newX = cenP.x - 64 * cos(degree);
	auto newY = cenP.y - 64 * sin(degree);
	auto newPosition = Vec2(newX, newY);
	return newPosition;
}
