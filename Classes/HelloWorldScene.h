#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	HelloWorld();
    
    // a selector callback
	void addSprite();
    void menuCloseCallback(cocos2d::Ref* pSender);
	void createMenu();

	void loadingCallBack(cocos2d::Texture2D *texture);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	Label *_labelLoading;
	Label *_labelPercent;
	int _numberOfSprites;
	int _numberOfLoadedSprites;
};



#endif // __HELLOWORLD_SCENE_H__
