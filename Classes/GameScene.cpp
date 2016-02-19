/******************************
游戏页面
*/

#include "GameScene.h"
#include "PauseLayer.h"
#include "ActorBall.h"
#include "EnemyBall.h"

USING_NS_CC;



Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	/*****************************
	测试数目
	1.敌人的数量等于4
	2.能量球数量等于2
	*/
	int enemyNum = 4;
	int energyBallNum = 2;

	struct levelInfo* level01 = new struct levelInfo;
	level01->level_enemyNum = enemyNum;
	level01->level_energyNum = energyBallNum;
	level01->level_goldCoinNum = 1;


	auto scene = Scene::createWithPhysics();
	auto world = scene->getPhysicsWorld();
	//world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	world->setGravity(Vec2(0, 0));
	Size visibleSize = Director::getInstance()->getVisibleSize();

	
	// game's layer. 游戏个layer层
	int maxBgPic = 4;
	auto bgLayer = LayerColor::create(Color4B(152,245,255,255));
	this->addChild(bgLayer, 0);

	midLayer = Layer::create();
	this->addChild(midLayer, 10);

	auto topLayer = Layer::create();
	this->addChild(topLayer, 20);


	// boder box 添加游戏边框
	auto emptyNode = Node::create();
	emptyNode->setContentSize(Size(visibleSize * 1));
	emptyNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	auto boderBox = PhysicsBody::createEdgeBox(emptyNode->getContentSize(), PhysicsMaterial(0.1, 1, 0), 10.0f);
	boderBox->setCategoryBitmask(0x10010000);
	boderBox->setContactTestBitmask(0x10000000);
	boderBox->setCollisionBitmask(0x00011110);
	emptyNode->setPhysicsBody(boderBox);
	emptyNode->setTag(300);
	
	this->addChild(emptyNode);
	
	// background pic...背景图
	GameScene::getBGPic(maxBgPic);	
	
	// Score，当前得分
	auto gameScore = Label::createWithTTF("0", "fonts/Impact.ttf", 52);
	gameScore->setPosition(Point(visibleSize.width*0.08, visibleSize.height*0.94));
	topLayer->addChild(gameScore);

	// energyBall,能量球
	int num_energyBall = 2;
	for (int i = 1; i <= num_energyBall; i++)
	{
		auto tempSprite = Sprite::createWithSpriteFrameName("score_empty.png");
		tempSprite->setPosition(Vec2(visibleSize.width*0.08+36*(i-1), visibleSize.height*0.89));
		topLayer->addChild(tempSprite);
		tempSprite->setTag(100 + i);
	}
	// 添加能量球
	for (int i = 1; i <= energyBallNum; i++)
	{
		GameScene::addEnergyBall();
	}

	// gold coin,金币
	auto goldIcon = Sprite::createWithSpriteFrameName("goldcoin.png");
	goldIcon->setPosition(Point(visibleSize.width*0.88, visibleSize.height*0.955));
	topLayer->addChild(goldIcon);
	goldIcon->setScale(0.7f);
	
	auto goldLabel = Label::createWithTTF("27","fonts/Impact.ttf", 30);
	goldLabel->setPosition(Point(visibleSize.width*0.94, visibleSize.height*0.955));
	topLayer->addChild(goldLabel);

	GameScene::addGoldCoin();

	// btn_pause暂停按钮
	GameScene::pauseMenu(topLayer);
	ActorBall actor;

	GameScene::addGameBorder();

	// 添加主角-红蓝球
	auto actorNode = Node::create();	//actor节点
	midLayer->addChild(actorNode);
	actorNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	actorRed = actor.actorBallRed();//红球
	actorRed->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	auto body = PhysicsBody::createCircle(actorRed->getContentSize().width / 2);
	body->setGravityEnable(false);
	body->setCategoryBitmask(0x00100001);
	body->setContactTestBitmask(0x01000000);
	body->setCollisionBitmask(0x00000001);
	actorRed->setPhysicsBody(body);
	midLayer->addChild(actorRed);
	log("actorRed's tag:  %d", actorRed->getTag());
		
	actorBlue = actor.actorBallBlue();//蓝球
	actorBlue->setPosition(visibleSize.width / 2 + 64, visibleSize.height / 2);
	auto body1 = PhysicsBody::createCircle(actorBlue->getContentSize().width/2);
	body1->setGravityEnable(false);
	body1->setCategoryBitmask(0x00100001);
	body1->setContactTestBitmask(0x01000000);
	body1->setCollisionBitmask(0x00000001);
	actorBlue->setPhysicsBody(body1);
	midLayer->addChild(actorBlue);
	log("actorBlue's tag:  %d", actorBlue->getTag());

	curCenterSprite = actorRed;

	// 添加阴影1
	auto s_shadowUp = GameScene::addShadowUp(actorBlue);
	auto s_shadowDown = GameScene::addShadowDown(actorRed);

	// 红蓝球的运动中心点
	schedule(schedule_selector(GameScene::updateCustem), 0, kRepeatForever, 0);

	// 场景跟随主角精灵而移动。Scene follow the Actor
	//this->runAction(Follow::create(curCenterSprite, Rect(0, 0, visibleSize.width * 2, visibleSize.height)));


	//// 添加敌人
	//int enemyIndex = 200;
	for (int i = 1; i <= enemyNum; i++)
	{
		auto enemy = addEnemy(actorRed);
		midLayer->addChild(enemy);
// 		enemy->setTag(enemyIndex);
// 		enemyIndex++;
// 		log("%d", enemyIndex);
	}

	// 镜头跟随移动




	// toplayer 的触摸事件
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* pTouch,Event* pEvent){
		static int centerNum = 1;
		if (centerNum == 1)
		{
			log("1");
			centerNum = 2;
			curCenterSprite = actorBlue;
			actorRed->getChildByTag(502)->removeFromParent();
			actorBlue->getChildByTag(501)->removeFromParent();
			auto s_shadowUp = GameScene::addShadowUp(actorRed);
			auto s_shadowDown = GameScene::addShadowDown(actorBlue);
			this->runAction(Follow::create(curCenterSprite, Rect(0, 0, visibleSize.width*1,visibleSize.height*1)));

			return true;
		}
		else{
			log("2");
			centerNum = 1;
			curCenterSprite = actorRed;
			actorRed->getChildByTag(501)->removeFromParent();
			actorBlue->getChildByTag(502)->removeFromParent();
			auto s_shadowUp = GameScene::addShadowUp(actorBlue);
			auto s_shadowDown = GameScene::addShadowDown(actorRed);
			this->runAction(Follow::create(curCenterSprite, Rect(0, 0, visibleSize.width*1, visibleSize.height*1)));

			return true;
		}
		return true;
	};
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, topLayer);




	return true;
}

int GameScene::getRandom(int maxNum) //random number.
{
	int t = random(1, maxNum);
	return t;
}

void GameScene::getBGPic(int maxBgPic) //random an int number, then get the background pic.
{
	int bgOrder = GameScene::getRandom(maxBgPic);
	int* p_bgOrder = &bgOrder;
	char szName[50] = { 0 };
	sprintf(szName, "res/bg_%d.png", *p_bgOrder);
	auto bgPic = Sprite::create(szName);
	bgPic->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
	bgPic->setScale(1.5f);
	this->addChild(bgPic);
}


void GameScene::pauseMenu(Layer* layer) // pause button
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto menu = Menu::create();
	menu->setContentSize(Size(200, 200));
	menu->setPosition(Vec2(origin.x + visibleSize.width *0.9, origin.y + visibleSize.height *0.91));
	menu->setAnchorPoint(Point(0.5, 0.5));
	layer->addChild(menu);

	auto btnNormal_play = Sprite::createWithSpriteFrameName("pause_nor.png");
	auto btnSelect_play = Sprite::createWithSpriteFrameName("pause_click.png");
	auto btn_play = MenuItemSprite::create(btnNormal_play, btnSelect_play,
		[&](Ref* sender)
	{
		Director::getInstance()->pause();
		log("Pause");
		auto pauseLayer = PauseLayer::create();
		this->addChild(pauseLayer, 30);
	});
	
	btn_play->setPosition(0, 0);
	btn_play->setScale(0.8f);
	menu->addChild(btn_play);
	
	return;
}

void GameScene::addGameBorder() //Add game's border box.
{

	auto drawNode = DrawNode::create();
	Size s = Director::getInstance()->getVisibleSize();
	Vec2 ps[4] =
	{
		Vec2(s.width*0.01, s.height*0.01),
		Vec2(s.width*0.99, s.height*0.01),
		Vec2(s.width*0.99, s.height*0.99),
		Vec2(s.width*0.01, s.height*0.99),
	};
	drawNode->drawPoly(ps, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
	this->addChild(drawNode);
}

Sprite* GameScene::addEnemy(Sprite* s) //add enemy
{
	EnemyBall newEnemy;
	Sprite* enemy = newEnemy.enemy();
	float vecPointX = s->getPosition().x - enemy->getPosition().x;
	float vecPointY = s->getPosition().y - enemy->getPosition().y;
	enemy->getPhysicsBody()->setVelocity(Vect(vecPointX/10, vecPointY/10));
	log("Add Enemy");
	return enemy;
}

void GameScene::updateCustem(float dt)
{
	ActorBall actorBall;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// 判断是否在边框界限内
	static float count = 0.08f;

	if (actorRed->getPosition().x<30 || actorRed->getPosition().y<30 ||
		actorBlue->getPosition().x<30 || actorBlue->getPosition().y<30 ||
		actorRed->getPosition().x >(visibleSize.width - 30) || actorRed->getPosition().y >(visibleSize.height - 30) ||
		actorBlue->getPosition().x >(visibleSize.width - 30) || actorBlue->getPosition().y >(visibleSize.height - 30))
	{
		count = 0 - count;
	}
	
	if (curCenterSprite == actorRed)
	{
		actorBlue->setPosition(actorBall.rotateClock(actorRed, actorBlue, -count));
	}
	else {
		//curCenterSprite = actorBlue;
		actorRed->setPosition(actorBall.rotateClock(actorBlue, actorRed, count));
	}

}

Sprite* GameScene::addShadowUp(Sprite* s)
{
	// 添加阴影1:边球的阴影
	auto shadowUp = Sprite::createWithSpriteFrameName("small_shadow.png");
	shadowUp->setPosition(Vec2(s->getContentSize().width / 2 + 8, s->getContentSize().width / 2-8));
	shadowUp->setAnchorPoint(Vec2(0.5, 0.5));
	s->addChild(shadowUp, -5);
	shadowUp->setTag(501);
	return shadowUp;
}

Sprite* GameScene::addShadowDown(Sprite* s)
{
	// 添加阴影2:中心球的阴影
	auto shadowDown = Sprite::createWithSpriteFrameName("small_shadow.png");
	shadowDown->setPosition(Vec2(s->getContentSize().width / 2 + 2, s->getContentSize().width / 2 - 2));
	shadowDown->setAnchorPoint(Vec2(0.5, 0.5));
	s->addChild(shadowDown, -5);
	shadowDown->setTag(502);
	return shadowDown;
}


void GameScene::onEnter()
{
	Layer::onEnter();

	// 碰撞检测
	auto contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = [=](PhysicsContact& contact){
		Sprite* spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
		Sprite* spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
		int tagA = spriteA->getTag();
		int tagB = spriteB->getTag();
		log("on contact begin");
		log("tagA:   %d,  tagB:   %d", tagA, tagB);

		// actor和enemy碰撞 
		if ((tagA == 100 && tagB == 200) || (tagA == 200 && tagB == 100))	
		{
			if (tagA == 100)
			{
				//Director::getInstance()->pause();
				spriteB->removeFromParent();
			}
			if (tagB == 100)
			{
				//Director::getInstance()->pause();
				spriteA->removeFromParent();
			}
		}

		// actor和goldcoin碰撞
		if ((tagA == 100 && tagB == 500) || (tagA == 500 && tagB == 100))
		{
			if (tagA == 500)
			{
				//Director::getInstance()->pause();
				spriteA->removeFromParent();
			}
			if (tagB == 500)
			{
				//Director::getInstance()->pause();
				spriteB->removeFromParent();
			}
		}

		// actor和energyball碰撞
		if ((tagA == 100 && tagB == 400) || (tagA == 400 && tagB == 100))
		{
			if (tagA == 400)
			{
				//Director::getInstance()->pause();
				spriteA->removeFromParent();
			}
			if (tagB == 400)
			{
				//Director::getInstance()->pause();
				spriteB->removeFromParent();
			}
		}

		// enemy和边墙碰撞
		if (tagA == 200 && tagB == 300 || tagA == 300 && tagB ==200 )	
		{
			if (tagA==200)
			{
				spriteA->removeFromParent();
				auto enemy = addEnemy(actorRed);
				midLayer->addChild(enemy);
			}
			if (tagB == 200)
			{
				spriteB->removeFromParent();
				auto enemy = addEnemy(actorRed);
				midLayer->addChild(enemy);
			}
		}

		return true;
	};
	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(contactListener, 1);

}

void GameScene::onExit()
{
	Layer::onExit();
	log("gamescene exit");
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

void GameScene::addEnergyBall()
{

	int x = random(80,(int)(Director::getInstance()->getVisibleSize().width-80));
	int y = random(80, (int)(Director::getInstance()->getVisibleSize().height - 80));
	auto energyball = Sprite::createWithSpriteFrameName("scorepoint_1.png");
	energyball->setPosition(Vec2(x, y));
	energyball->setTag(400);

	auto energyBallPoint_1 = Sprite::createWithSpriteFrameName("scorepoint_2.png");
	energyBallPoint_1->setPosition(Vec2(energyball->getContentSize().width / 2, energyball->getContentSize().height / 2));
	energyBallPoint_1->runAction(RepeatForever::create(RotateBy::create(0.1, 30)));
	energyBallPoint_1->setAnchorPoint(Vec2(0.53, 0.70));

	auto energyBallPoint_2 = Sprite::createWithSpriteFrameName("scorepoint_3.png");
	energyBallPoint_2->setPosition(Vec2(energyball->getContentSize().width / 2, energyball->getContentSize().height / 2));
	energyBallPoint_2->runAction(RepeatForever::create(RotateBy::create(0.1, -30)));
	energyBallPoint_2->setAnchorPoint(Vec2(0.505, 0.495));

	auto energyBody = PhysicsBody::createCircle(energyBallPoint_1->getContentSize().width/2, PhysicsMaterial(1,1,1));
	energyBody->setCategoryBitmask(0x01000100);
	energyBody->setContactTestBitmask(0x00100000);
	energyBody->setCollisionBitmask(0x00011110);
	energyBody->setDynamic(false);
	energyball->setPhysicsBody(energyBody);

	energyball->addChild(energyBallPoint_1);
	energyball->addChild(energyBallPoint_2);
	
	this->addChild(energyball);
}

void GameScene::addGoldCoin()
{

	int x = GameScene::getRandom(Director::getInstance()->getVisibleSize().width);
	int y = GameScene::getRandom(Director::getInstance()->getVisibleSize().height);
	auto goldCoin = Sprite::createWithSpriteFrameName("goldcoin.png");
	goldCoin->setPosition(Vec2(x, y));
	goldCoin->setTag(500);

	auto energyBody = PhysicsBody::createCircle(goldCoin->getContentSize().width / 2, PhysicsMaterial(1, 1, 1));
	energyBody->setGravityEnable(false);
	energyBody->setCategoryBitmask(0x01000010);
	energyBody->setContactTestBitmask(0x00100000);
	energyBody->setCollisionBitmask(0x00011110);
	goldCoin->setPhysicsBody(energyBody);
	goldCoin->getPhysicsBody()->setVelocity(Vect(random(50,80),random(50,80)));

	this->addChild(goldCoin);
}
