#pragma once
class ArrowPattern
{
public:
	virtual ~ArrowPattern() = default;

	virtual void start() = 0;
	virtual	void update(float dt) = 0;
	virtual void reset() = 0;
	virtual bool isCompleted() = 0;
};

