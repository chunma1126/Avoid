#pragma once
#include "cocos2d.h"
#include <string>
#include <format>

class TimeView
{
public:
	void init();
	void setLabel(float _time) 
	{
		std::string formatted = std::format("{:.2f}", _time);
		timeLabel->setString(formatted);
	}
	cocos2d::Label* getLabel() { return timeLabel; }
private:
	cocos2d::Label* timeLabel;
};

