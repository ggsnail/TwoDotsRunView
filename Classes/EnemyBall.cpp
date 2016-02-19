#include "EnemyBall.h"

Sprite* EnemyBall::enemy()
{
	Sprite* sprite = Sprite::createWithSpriteFrameName("enemy_a.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size spriteSize = sprite->getContentSize();
	int visibleWidth = visibleSize.width, visibleHeight = visibleSize.height;
	int spriteWidth = spriteSize.width, spriteHeight = spriteSize.height;

	//log("Sprite's width is : %d..height is : %d", spriteWidth, spriteHeight);
	//log("Visibe's width is : %d..height is : %d", visibleWidth, visibleHeight);
	/*
	敌人生成坐标规则：
	1. 首先选择计算方法
	2. 假设方法一：
		当X<2倍直径时
		Y的取值范围为中部
	3.循环计算
	*/
	int innerEdge = 1.5;//敌人生成点-内边
	int outEdge = 1;//敌人生成点-外边
	int pointX = 0,pointY = 0;
	int count = random(1, 4);
	switch (count)
	{
		case 1:
			// X在左边，Y在全局
			pointX = random(spriteWidth*outEdge, spriteWidth * innerEdge);
			pointY = random(spriteHeight * innerEdge, visibleHeight - spriteHeight * innerEdge);
			break;
		case 2:
			// X在右边，Y在全局
			pointX = random(visibleWidth - innerEdge*spriteWidth, visibleWidth - spriteWidth*outEdge);
			pointY = random(spriteHeight * innerEdge, visibleHeight - spriteHeight * innerEdge);
			break;
		case 3:
			// X在全局，Y在底部
			pointX = random(spriteWidth*outEdge, visibleWidth - spriteWidth*outEdge);
			pointY = random(spriteHeight*outEdge, spriteHeight * innerEdge);
			break;
		case 4:
			// X在全局，Y在顶部
			pointX = random(spriteWidth*outEdge, visibleWidth - spriteWidth*outEdge);
			pointY = random(visibleHeight - spriteHeight * innerEdge, visibleHeight - spriteHeight*outEdge);
			break;
	}


	//log("x:  %d", pointX);
	//log("y:  %d", pointY);
	
	// Enemy's self-rotation.
	sprite->setPosition(Vec2(pointX, pointY));
	auto enemyRotate = RotateBy::create(0.1, -10);
	sprite->runAction(RepeatForever::create(enemyRotate));

	// Enemy's physics body.
	auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2,PhysicsMaterial(1,1,0));
	body->setGravityEnable(false);
	body->setCategoryBitmask(0x11001000);
	body->setContactTestBitmask(0x10100000);
	body->setCollisionBitmask(0x00011110);
	sprite->setPhysicsBody(body);
	sprite->setTag(200);
	log("Enemy's tag:   %d", sprite->getTag());

	return sprite;
}

