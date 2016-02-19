/******************************
游戏页面
*/

#include "PauseLayer.h"

USING_NS_CC;



Scene* PauseLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = PauseLayer::create();
	scene->addChild(layer);
	return scene;
}

bool PauseLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bgLayer = LayerColor::create(Color4B(0,0,0,125));
	this->addChild(bgLayer);

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch*, Event*){ return true; };

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		
	auto menu = Menu::create();
	bgLayer->addChild(menu);
	menu->setPosition(0, 0);

	// 音效开关按钮
	auto itemSound = MenuItemImage::create("res/setting/sound_on.png","res/setting/sound_off.png",
		[&](Ref* sender)
	{
		log("sound on/off");
	});
	itemSound->setPosition(Vec2(visibleSize.width *0.3, visibleSize.height*0.75));
	menu->addChild(itemSound);
	PauseLayer::AddSpriteBorder(itemSound);

	// 音乐开关按钮
	auto itemMusic = MenuItemImage::create("res/setting/music_on.png", "res/setting/music_off.png",
		[&](Ref* sender)
	{
		log("music of/off");
	});
	itemMusic->setPosition(Vec2(visibleSize.width *0.7, visibleSize.height*0.75));
	menu->addChild(itemMusic);
	PauseLayer::AddSpriteBorder(itemMusic);

	// 评分按钮
	auto itemRate = MenuItemImage::create("res/setting/rate.png", "res/setting/rate.png",
		[&](Ref* sender)
	{
		log("rate");
	});
	itemRate->setPosition(Vec2(visibleSize.width *0.3, visibleSize.height*0.57));
	itemRate->setScale(0.8f);
	menu->addChild(itemRate);
	PauseLayer::AddSpriteBorder(itemRate);

	// 吐槽按钮
	auto itemFeedBack = MenuItemImage::create("res/setting/feedback.png","res/setting/feedback.png",
		[&](Ref* sender)
	{
		log("feed back");
	});
	itemFeedBack->setPosition(Vec2(visibleSize.width *0.7, visibleSize.height*0.57));
	itemFeedBack->setScale(0.8f);
	menu->addChild(itemFeedBack);
	PauseLayer::AddSpriteBorder(itemFeedBack);

	// 关于我们按钮
	auto itemAboutUs = MenuItemLabel::create(LabelTTF::create("About Us", "fonts/Impact.ttf", 40),
		[&](Ref* sender)
	{
		log("about us.");
	});
	itemAboutUs->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.385));
	menu->addChild(itemAboutUs);
	PauseLayer::AddTextBorder(itemAboutUs);


	// 返回游戏按钮
	auto itemReturn = MenuItemLabel::create(LabelTTF::create("Continue", "fonts/Impact.ttf", 40),
		[&](Ref* sender)
	{
		log("return game.");
		this->removeFromParent();
		Director::getInstance()->resume();
	});
	itemReturn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.24));
	menu->addChild(itemReturn);
	PauseLayer::AddTextBorder(itemReturn);

	return true;
}
//
void PauseLayer::AddTextBorder(MenuItemLabel * l)
{
	auto drawNode = DrawNode::create();
	auto p = l->getPosition();
	Size s = Director::getInstance()->getVisibleSize();
	Vec2 ps[4] =
	{
		Vec2(p.x - s.width*0.33, p.y - s.height*0.05),
		Vec2(p.x + s.width*0.33, p.y - s.height*0.05),
		Vec2(p.x + s.width*0.33, p.y + s.height*0.05),
		Vec2(p.x - s.width*0.33, p.y + s.height*0.05),
	};
	drawNode->drawPoly(ps, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
	this->addChild(drawNode);
}

void PauseLayer::AddSpriteBorder(MenuItemImage *sp)
{
	auto drawNode = DrawNode::create();
	auto p = sp->getPosition();
	Size s = Director::getInstance()->getVisibleSize();
	Vec2 ps[4] =
	{
		Vec2(p.x - s.width*0.13, p.y - s.height*0.04),
		Vec2(p.x + s.width*0.13, p.y - s.height*0.04),
		Vec2(p.x + s.width*0.13, p.y + s.height*0.04),
		Vec2(p.x - s.width*0.13, p.y + s.height*0.04),
	};
	drawNode->drawPoly(ps, 4, true, Color4F(1.0, 1.0, 1.0, 1.0));
	this->addChild(drawNode);
}

