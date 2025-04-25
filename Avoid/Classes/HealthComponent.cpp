#include "HealthComponent.h"
#include "Action.h"
#include "cocos2d.h"

HealthComponent::HealthComponent()
{
	init();
}

HealthComponent::~HealthComponent()
{

}

void HealthComponent::init()
{
	currentHp = maxHp;
}

void HealthComponent::takeDamage(int _damage)
{
	onDamageEvents.invoke(_damage);

	currentHp -= _damage;

	CCLOG("%d" , currentHp);

	if (currentHp <= 0) {
		dead();
	}

}

void HealthComponent::takeHeal(int _heal)
{
	onHealEvents.invoke(_heal);

	currentHp += _heal;
	if (currentHp >= maxHp)
		currentHp = maxHp;

}

void HealthComponent::dead()
{
	onDeadEvents.invoke();
}
