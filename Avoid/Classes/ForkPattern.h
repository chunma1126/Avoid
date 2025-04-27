#pragma once
#include "ArrowPattern.h"
class ForkPattern : public ArrowPattern
{
public:
	virtual ~ForkPattern();
	void start() override;
	void update(float dt) override;
	void reset() override;
	bool isCompleted() override;
};

