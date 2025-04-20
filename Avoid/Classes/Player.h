#pragma once
#include "cocos2d.h"
#include <set>
class Player : public cocos2d::Node 
{
public:
    virtual bool init() override;
    virtual void update(float dt) override;


    void clampPosition();
    void move(float dt);

    CREATE_FUNC(Player);
private:
    std::map<cocos2d::EventKeyboard::KeyCode, bool> _keyState;


    cocos2d::Sprite* _sprite;
    cocos2d::PhysicsBody* _rigidBody;

    const float _collisionScale = 10;
	float _speed = 8000;
	bool _isMoving;

};

