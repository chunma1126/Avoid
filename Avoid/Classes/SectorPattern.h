#pragma once
#include "ArrowPattern.h"
class SectorPattern : public ArrowPattern
{
public:
	SectorPattern(int direction) { _direction = direction; };
	virtual ~SectorPattern();
	void start() override;
	void update(float dt) override;
	void reset() override;
	bool isCompleted() override;
private:
	int _direction = 0;
};

