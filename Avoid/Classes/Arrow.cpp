#include "Arrow.h"
#include "cocos2d.h"
#include "ArrowPool.h"

USING_NS_CC;

bool Arrow::init()
{
    if (!Node::init()) 
    {
        return false;
    }

    //sprite init
    {
        _sprite = Sprite::create("Arrow.png");
        _sprite->setScale(0.2f);
        addChild(_sprite);
    }

    {
        int widht = _sprite->getContentSize().width * _sprite->getScale();
        int height = _sprite->getContentSize().height * _sprite->getScale();

        _rigidBody = PhysicsBody::createBox(Size(widht, height), PHYSICSBODY_MATERIAL_DEFAULT);

        _rigidBody->setGravityEnable(false);
        _rigidBody->setDynamic(true);
        _rigidBody->setContactTestBitmask(0xFFFFFFFF);

        setPhysicsBody(_rigidBody);
    }

    scheduleUpdate();
    return true;
}

void Arrow::update(float dt)
{
    auto pos = getPosition();
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto originSize = Director::getInstance()->getVisibleOrigin();

	if (pos.x < originSize.x || pos.x > screenSize.width + originSize.x ||
		pos.y < originSize.y || pos.y > screenSize.height + originSize.y)
	{
        ArrowPool::getInstance().Push(this);
        return;
	}

    _rigidBody->setVelocity(_direction * _speed * dt);
    rotate();

}

void Arrow::rotate()
{
    Vec2 velocity = _rigidBody->getVelocity();
    if (velocity.length() > 0)
    {
        velocity.normalize(); // 벡터의 길이를 1로 정규화하여 방향만 고려
        float angle = CC_RADIANS_TO_DEGREES(velocity.getAngle()); // 벡터의 각도 계산
        setRotation(angle); // 화살 회전
    }
}




