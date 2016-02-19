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
		int level_energyNum; //��ǰ�ؿ�����������
		int level_goldCoinNum; //��ǰ�ؿ��������
		int level_enemyNum; //��ǰ�ؿ���������
	};

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	Sprite* actorRed;
	Sprite* actorBlue;
	Sprite* curCenterSprite;
	Layer* midLayer;
	int* score_goldcoin;//�ܽ����
	int* score_current; //��ǰ��Ϸ�÷�
	int* score_history; //��ʷ��߷�


};

#endif // __GAMESCENE_H__