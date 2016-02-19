#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	virtual void onEnter();
	virtual void onExit();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	void updateCustem(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void pauseMenu(Layer* layer);
	// get bgpic's num;
	int getRandom(int maxNum);
	void getBGPic(int maxBgPic);
	void addGameBorder();

	Sprite* addEnemy(Sprite* s);
	Sprite* addShadowUp(Sprite* s);
	Sprite* addShadowDown(Sprite* s);
	void addEnergyBall();
	void addGoldCoin();

	struct levelInfo
	{
		int level_energyNum; //当前关卡能量球总数
		int level_goldCoinNum; //当前关卡金币总数
		int level_enemyNum; //当前关卡敌人数量
	};

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	Sprite* actorRed;
	Sprite* actorBlue;
	Sprite* curCenterSprite;
	Layer* midLayer;
	int* score_goldcoin;//总金币数
	int* score_current; //当前游戏得分
	int* score_history; //历史最高分


};

#endif // __GAMESCENE_H__