#ifndef __PAUSELAYER_H__
#define __PAUSELAYER_H__

#include "cocos2d.h"

class PauseLayer : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void AddTextBorder(cocos2d::MenuItemLabel* l);
	void AddSpriteBorder(cocos2d::MenuItemImage* s);
	// implement the "static create()" method manually
	CREATE_FUNC(PauseLayer);
};

#endif // __PAUSELAYER_H__