#include "CirclePattern.h"

CirclePattern::~CirclePattern()
{
  
}

void CirclePattern::start()
{
    _completeTime = 4.5;
    _arrowCount = 18;
    _arrowSpeed = 7000;

    _arrowInteval = _angle / _arrowCount;

    Vec2 visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _circleCenter = Vec2(
        visibleSize.x * 0.5f + origin.x,
        visibleSize.y * 0.3f + origin.y  
    );

    auto rotateAction = RotateBy::create(_fireTime, -_arrowInteval);
    auto repeateRoate = RepeatForever::create(rotateAction);
    spawnerArrow = ArrowPool::getInstance().pop(_circleCenter, _circleCenter, 0.1f);
    spawnerArrow->setIngnoreRotate(true);
    spawnerArrow->runAction(repeateRoate);
}

void CirclePattern::update(float dt)
{
    _timer += dt;
    _completeTimer += dt;

    if (_completeTime - _completeTimer <= _fadeOutTime)
    {
        auto fadeOutAction = FadeOut::create(_fadeOutTime);
        spawnerArrow->runAction(fadeOutAction);
    }

    if (_timer >= _fireTime)
    {
        _timer = 0;

        float angleDegree = _arrowInteval * (_fireIndex++ % _arrowCount);
        float angle = CC_DEGREES_TO_RADIANS(angleDegree);
        Vec2 dir = Vec2(cosf(angle), sinf(angle));

        ArrowPool::getInstance().pop(_circleCenter, dir, _arrowSpeed);
    }
}

void CirclePattern::reset()
{
	ArrowPool::getInstance().push(spawnerArrow);
}

bool CirclePattern::isCompleted()
{
	return _completeTimer >= _completeTime;
}
