#include "SectorPattern.h"
#include "cocos2d.h"

SectorPattern::~SectorPattern()
{
}

void SectorPattern::start()
{
	_completeTime = 2.5f;

    float centerAngleDeg = 90.0f;
    float sectorAngleDeg = 60.0f;

    float startAngleDeg = centerAngleDeg - sectorAngleDeg / 2.0f;
    float endAngleDeg = centerAngleDeg + sectorAngleDeg / 2.0f;

    int count = 5;
    for (int i = 0; i < count; ++i)
    {
        float t = (float)i / (count - 1);
        float angleDeg = startAngleDeg + (endAngleDeg - startAngleDeg) * t;
        float angleRad = CC_DEGREES_TO_RADIANS(angleDeg);

        cocos2d::Vec2 dir(cosf(angleRad), sinf(angleRad));

        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Vec2 pos = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250);

        ArrowPool::getInstance().Pop(pos, dir, _arrowSpeed);
    }

}

void SectorPattern::update(float dt)
{
	_timer += dt;

    

}

void SectorPattern::reset()
{
}

bool SectorPattern::isCompleted()
{
	return _timer >= _completeTime;
}
