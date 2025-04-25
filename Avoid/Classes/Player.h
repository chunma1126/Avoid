#pragma once
#include "cocos2d.h"
#include "HealthComponent.h"
#include <unordered_map>

class Player : public cocos2d::Node 
{
public:
    virtual bool init() override;
    virtual void update(float dt) override;

    ~Player();

    CREATE_FUNC(Player);
private:
    void clampPosition();
    void move(float dt);
    bool onCollisionBegin(cocos2d::PhysicsContact& contact);
    void FlashFeedback();
private:
    std::unordered_map<cocos2d::EventKeyboard::KeyCode, bool> _keyState;

    cocos2d::Sprite* _sprite;
    cocos2d::PhysicsBody* _rigidBody;

    HealthComponent health;
   


private:
    const float _collisionScale = 10;
	float _speed = 8000;

	bool _isMoving;

};

