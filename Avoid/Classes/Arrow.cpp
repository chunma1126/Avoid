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
        ArrowPool::Push(this);
        return;
	}

    _rigidBody->setVelocity(_direction * _speed * dt);


}




