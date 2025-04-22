#include "UIController.h"


bool UIController::init()
{
	if (Node::init() == false)
		return false;
	_timeCount.init();
	_timeView.init();

	scheduleUpdate();

	return true;
}

void UIController::update(float dt)
{
	_timeCount.addTime(dt);
	_timeView.setLabel(_timeCount.getTime());
	CCLOG("%d" , _timeCount.getTime());
}

void UIController::setScene(cocos2d::Scene* scene)
{
	_scene = scene;
	_timeView.addLabel(*scene);
}


