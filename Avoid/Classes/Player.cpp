#include "Player.h"
#include "Enum.h"
#include "HealthComponent.h"
USING_NS_CC;

bool Player::init()
{
    if (!Node::init()) {
        return false;
    }
    
    //sprite init
    {
        _sprite = Sprite::create("character.png");
        _sprite->setScale(0.2f);
        addChild(_sprite);
    }

    //rigidbody init
    {
        _rigidBody = PhysicsBody::createCircle(_collisionScale, PHYSICSBODY_MATERIAL_DEFAULT);
        _rigidBody->setGravityEnable(false);
        _rigidBody->setDynamic(true);

        _rigidBody->setCategoryBitmask(LayerMask::PLAYER);      
        //_rigidBody->setCollisionBitmask(LayerMask::ARROW);      
        _rigidBody->setContactTestBitmask(LayerMask::ARROW);

        _rigidBody->setTag(LayerMask::PLAYER);

        setPhysicsBody(_rigidBody);
    }

    //input init
    {
        auto keyboardEvent = EventListenerKeyboard::create();

        keyboardEvent->onKeyPressed = [=](EventKeyboard::KeyCode key, Event*) {
            _keyState[key] = true;
            };

        keyboardEvent->onKeyReleased = [=](EventKeyboard::KeyCode key, Event*) {
            _keyState[key] = false;
            };

        _eventDispatcher->addEventListenerWithFixedPriority(keyboardEvent, 1);
    }
    
    //rigidbodyEvent init
    {
        auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = std::bind(&Player::onCollisionBegin, this, std::placeholders::_1);

        _eventDispatcher->addEventListenerWithFixedPriority(contactListener,1);
    }

    health = new HealthComponent();
    
    health->onDamageEvents.add([this](int dmg) {
        FlashFeedback(dmg);
        });


    scheduleUpdate();
    return true;
}

Player::~Player()
{
    if (health != nullptr) {
        delete health;
        health = nullptr;
    }

}

void Player::update(float dt)
{
    move(dt);

}



void Player::clampPosition()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto originSize = Director::getInstance()->getVisibleOrigin();
    auto pos = getPosition();
    Size spriteSize = _sprite->getContentSize() * _sprite->getScale();

    float halfWidth = spriteSize.width / 2.0f;
    float halfHeight = spriteSize.height / 2.0f;

    float clampedX = clampf(pos.x, halfWidth + originSize.x, visibleSize.width - halfWidth + originSize.x);
    float clampedY = clampf(pos.y, halfHeight + originSize.y, visibleSize.height - halfHeight + originSize.y);

    setPosition(Vec2(clampedX, clampedY));
}

void Player::move(float dt)
{
    Vec2 velocity;

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

    if (velocity.length() > _speed)
    {
        velocity.normalize();
        velocity *= _speed;
    }
	
    if (velocity.length() > 0)
        _isMoving = true;
    else {
        _isMoving = false;
    }
    
    _rigidBody->setVelocity(velocity * dt);

    clampPosition();
}

bool Player::onCollisionBegin(cocos2d::PhysicsContact& contact)
{
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();

    bool canCollision 
        =  (bodyA->getTag() == LayerMask::PLAYER && bodyB->getTag() == LayerMask::ARROW)
        || (bodyA->getTag() == LayerMask::ARROW  && bodyB->getTag() == LayerMask::PLAYER);

    //check physicsbody
    if (canCollision) {
        health->takeDamage(1);
    }
    else {
        return true;
    }


    return true;
}

void Player::FlashFeedback(int _damage)
{
    CCLOG("WTF");
}


