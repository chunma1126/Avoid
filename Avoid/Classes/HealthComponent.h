#pragma once
#include "Action.h"

class HealthComponent
{
public:
	HealthComponent();
	virtual ~HealthComponent();

	void takeDamage(int _damage);
	void takeHeal(int _heal);

	Action<int> onDamageEvents;
	Action<int> onHealEvents;
	Action<> onDeadEvents;
private:
	void init();
	void dead();

private:
	int maxHp = 10;
	int currentHp;

	

};