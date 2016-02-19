/*
本页面更改为进入游戏的资源加载页面
*/
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	/*
	1.Super init
	*/
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	FileUtils::getInstance()->addSearchPath("res");

	auto bgPic = Sprite::create("splash_bg.jpg");
	bgPic->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(bgPic);

	/*
	版权信息文件
	text01、02:原本中的官方名字和其他文字
	text03、04:GGSnail声明，仅限个人交流，禁止用于商业用途。
	*/

	auto text01 = Label::createWithTTF("TTZ STUDIO", "fonts/din-light.ttf", 24);
	text01->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.2));
	this->addChild(text01);
	auto text02 = Label::createWithTTF("HAVE MORE FUN", "fonts/din-light.ttf", 24);
	text02->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.2 - 28));
	text02->setTextColor(Color4B(102, 204, 153, 255));
	this->addChild(text02);
	auto text03 = Label::createWithTTF("GGSnail: The exchange of personal use only.", "fonts/din-light.ttf", 24);
	text03->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.2 - 56));
	this->addChild(text03);
	auto text04 = Label::createWithTTF("DO NOT USED FOR COMMERCIAL PURPOSES.", "fonts/din-light.ttf", 24);
	text04->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.2 - 82));
	this->addChild(text04);


	/*
	资源预加载
	sources preload
	*/
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/res_1.plist", "res/res_1.png");
	cache->addSpriteFramesWithFile("res/res_2.plist", "res/res_2.png");
	cache->addSpriteFramesWithFile("res/other.plist", "res/other.png");
	cache->addSpriteFramesWithFile("res/about.plist", "res/about.png");

	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/bg.mp3");
	//HelloWorld::HelloWorld();
    return true;
}

void HelloWorld::createMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto menu = Menu::create();
	menu->setContentSize(Size(200, 200));
	menu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height *0.45));
	menu->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(menu);

	auto btnNormal_play = Sprite::createWithSpriteFrameName("play_nor.png");
	auto btnSelect_play = Sprite::createWithSpriteFrameName("play_click.png");
	auto btn_play = MenuItemSprite::create(btnNormal_play, btnSelect_play,
		[&](Ref* sender)
	{
		Director::getInstance()->replaceScene(GameScene::createScene());
	});
	btn_play->setPosition(0, 0);
	btn_play->setScale(0.8f);
	menu->addChild(btn_play);
	return;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


HelloWorld::HelloWorld()
: _numberOfSprites(7)
, _numberOfLoadedSprites(0)
{
	auto size = Director::getInstance()->getWinSize();

	_labelLoading = Label::createWithTTF("loading...", "fonts/arial.ttf", 15);
	_labelPercent = Label::createWithTTF("%0", "fonts/arial.ttf", 15);

	_labelLoading->setPosition(Vec2(size.width / 2, size.height / 2 - 20));
	_labelPercent->setPosition(Vec2(size.width / 2, size.height / 2 + 20));
	this->addChild(_labelLoading);
	this->addChild(_labelPercent);

	// load textures

	Director::getInstance()->getTextureCache()->addImageAsync("res/bg_1.png", CC_CALLBACK_1(HelloWorld::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("res/bg_2.png", CC_CALLBACK_1(HelloWorld::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("res/bg_3.png", CC_CALLBACK_1(HelloWorld::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("res/bg_4.png", CC_CALLBACK_1(HelloWorld::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("res/share_bar_en.png", CC_CALLBACK_1(HelloWorld::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("res/share_bar_zh.png", CC_CALLBACK_1(HelloWorld::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("res/share_bar_zh_rTW.png", CC_CALLBACK_1(HelloWorld::loadingCallBack, this));



}

void HelloWorld::loadingCallBack(cocos2d::Texture2D *texture)
{
	++_numberOfLoadedSprites;
	char tmp[10];
	sprintf(tmp, "%%%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
	_labelPercent->setString(tmp);

	if (_numberOfLoadedSprites == _numberOfSprites)
	{
		this->removeChild(_labelLoading, true);
		this->removeChild(_labelPercent, true);
		HelloWorld::createMenu();
	}
}
