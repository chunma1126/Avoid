#include "Player.h"

USING_NS_CC;

bool Player::init()
{
    if (!cocos2d::Node::init()) {
        return false;
    }

    //sprite init
    {
        _sprite = Sprite::create("character.png");
        _sprite->setScale(0.3f);
        addChild(_sprite);
    }

    //rigidbody init
    {
        _rigidBody = PhysicsBody::createCircle(_collisionScale, PHYSICSBODY_MATERIAL_DEFAULT);
        _rigidBody->setGravityEnable(false);
        _rigidBody->setDynamic(true);
        _rigidBody->setContactTestBitmask(0xFFFFFFFF);
        setPhysicsBody(_rigidBody);
    }

    auto keyboardEvent = EventListenerKeyboard::create();

    keyboardEvent->onKeyPressed = [=](EventKeyboard::KeyCode key, Event*) {
        _keyState[key] = true;
        };

    keyboardEvent->onKeyReleased = [=](EventKeyboard::KeyCode key, Event*) {
        _keyState[key] = false;
        };

    _eventDispatcher->addEventListenerWithFixedPriority(keyboardEvent, 1);

    scheduleUpdate();
    return true;
}

void Player::update(float dt)
{
    cocos2d::Vec2 velocity = Vec2::ZERO;

    if (_keyState[EventKeyboard::KeyCode::KEY_A]) {
        velocity.x -= _speed;
    }
    if (_keyState[EventKeyboard::KeyCode::KEY_D]) {
        velocity.x += _speed;
    }
    if (_keyState[EventKeyboard::KeyCode::KEY_W]) {
        velocity.y += _speed;
    }
    if (_keyState[EventKeyboard::KeyCode::KEY_S]) {
        velocity.y -= _speed;
    }

    // 대각선 속도 보정
    if (velocity.length() > _speed) {
        velocity.normalize();
        velocity *= _speed;
    }

    _rigidBody->setVelocity(velocity * dt);
}


