#pragma once
class TimeCount
{
public:
	void increaseTime(float _dt) { time += _dt; }
	void init() { time = 0; }
	float getTime() const { return time; }
private:
	float time = 0;
};

