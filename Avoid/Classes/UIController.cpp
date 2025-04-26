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
		_bloodScreen = cocos2d::Sprite::create("bloodScreen.png");
		_bloodScreen->setPosition(screenCenter);

		float scaleX = visibleSize.width / _bloodScreen->getContentSize().width;
		float scaleY = visibleSize.height / _bloodScreen->getContentSize().height;

		_bloodScreen->setScale(scaleX, scaleY);
		_bloodScreen->setVisible(false);
		_bloodScreen->setOpacity(0);
	}

	// HealthBar init
	{
		_healthBar = HealthBar::create();
		_healthBar->setPosition({ screenCenter.x, visibleSize.height - 11 });
	}


	scheduleUpdate();

	return true;
}

void UIController::update(float dt)
{
	_timeCount.addTime(dt);
	_timeView.setLabel(_timeCount.getTime());
}

void UIController::setScene(cocos2d::Scene* scene)
{
	_scene = scene;

	_scene->addChild(_timeView.getLabel());
	_scene->addChild(_bloodScreen);
	_scene->addChild(_healthBar);

}

void UIController::playBloodScreen()
{
	_bloodScreen->setVisible(true);

	auto increaseAction = FadeTo::create(BLOOD_SCREEN_INCREASE);
	auto decreaseAction = FadeTo::create(BLODD_SCREEN_DECREASE);

	auto hideAction = CallFunc::create([this]() {
		_bloodScreen->setVisible(false);
		});

	_bloodScreen->runAction(Sequence::create(increaseAction, decreaseAction, hideAction, nullptr));
}

void UIController::setHealthBar(float _value)
{
	_healthBar->setHealthBar(_value);
}


