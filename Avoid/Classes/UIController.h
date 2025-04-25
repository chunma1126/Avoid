#pragma once
#include "cocos2d.h"
#include "TimeCount.h"
#include "TimeView.h"

class UIController : public cocos2d::Node
{
public:
	virtual bool init();
	virtual void update(float dt);
	void setScene(cocos2d::Scene* scene);
	void playBloodScreen();

	CREATE_FUNC(UIController);
private:
	TimeCount _timeCount;
	TimeView _timeView;

	cocos2d::Scene* _scene;
	cocos2d::Sprite* bloodScreen;

private:
	float increaseTime = 0.13f;
	float decreaseTime = 1.02f;

};

