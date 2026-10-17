#pragma once
#include "cocos2d.h"
#include <string>
#include <sstream>
#include <iomanip>

class TimeView
{
public:
	void init();
	void setLabel(float _time) 
	{
		std::stringstream ss;
		ss << "time : " << std::fixed << std::setprecision(2) << _time;
		std::string str = ss.str();
		
		timeLabel->setString(str);
	}
	cocos2d::Label* getLabel() { return timeLabel; }
private:
	cocos2d::Label* timeLabel;
};

