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
	���������������
	1. ����ѡ����㷽��
	2. ���跽��һ��
		��X<2��ֱ��ʱ
		Y��ȡֵ��ΧΪ�в�
	3.ѭ������
	*/
	int innerEdge = 1.5;//�������ɵ�-�ڱ�
	int outEdge = 1;//�������ɵ�-���
	int pointX = 0,pointY = 0;
	int count = random(1, 4);
	switch (count)
	{
		case 1:
			// X����ߣ�Y��ȫ��
			pointX = random(spriteWidth*outEdge, spriteWidth * innerEdge);
			pointY = random(spriteHeight * innerEdge, visibleHeight - spriteHeight * innerEdge);
			break;
		case 2:
			// X���ұߣ�Y��ȫ��
			pointX = random(visibleWidth - innerEdge*spriteWidth, visibleWidth - spriteWidth*outEdge);
			pointY = random(spriteHeight * innerEdge, visibleHeight - spriteHeight * innerEdge);
			break;
		case 3:
			// X��ȫ�֣�Y�ڵײ�
			pointX = random(spriteWidth*outEdge, visibleWidth - spriteWidth*outEdge);
			pointY = random(spriteHeight*outEdge, spriteHeight * innerEdge);
			break;
		case 4:
			// X��ȫ�֣�Y�ڶ���
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

