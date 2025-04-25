#include "UIController.h"

USING_NS_CC;

#define BLOOD_SCREEN_INCREASE increaseTime, 70
#define BLODD_SCREEN_DECREASE decreaseTime, 0

bool UIController::init()
{
	if (Node::init() == false)
		return false;
	

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 screenCenter = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	//timeLabel init
	{
		_timeCount.init();
		_timeView.init();
	}

	//bloodScreen init
	{
		bloodScreen = cocos2d::Sprite::create("bloodScreen.png");
		bloodScreen->setPosition(screenCenter);

		float scaleX = visibleSize.width / bloodScreen->getContentSize().width;
		float scaleY = visibleSize.height / bloodScreen->getContentSize().height;

		bloodScreen->setScale(scaleX, scaleY);
		bloodScreen->setVisible(false);
		bloodScreen->setOpacity(0);
	}

	scheduleUpdate();

	return true;
}

void UIController::update(float dt)
{
	_timeCount.addTime(dt);
	_timeView.setLabel(_timeCount.getTime());
	//CCLOG("%d" , _timeCount.getTime());
}

void UIController::setScene(cocos2d::Scene* scene)
{
	_scene = scene;

	scene->addChild(_timeView.getLabel());
	scene->addChild(bloodScreen);
}

void UIController::playBloodScreen()
{
	bloodScreen->setVisible(true);

	auto increaseAction = FadeTo::create(BLOOD_SCREEN_INCREASE);
	auto decreaseAction = FadeTo::create(BLODD_SCREEN_DECREASE);

	auto hideAction = CallFunc::create([this]() {
		bloodScreen->setVisible(false);
		});

	bloodScreen->runAction(Sequence::create(increaseAction, decreaseAction, hideAction, nullptr));
}


