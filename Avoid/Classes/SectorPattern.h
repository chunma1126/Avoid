#pragma once
#include "ArrowPattern.h"
class SectorPattern : public ArrowPattern
{
public:
	virtual ~SectorPattern();
	void start() override;
	void update(float dt) override;
	void reset() override;
	bool isCompleted() override;
private:

};

