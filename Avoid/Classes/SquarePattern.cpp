#include "SquarePattern.h"
#include "SectorPattern.h"
#include <algorithm>
#include <random>
#include <ctime>

SquarePattern::~SquarePattern()
{

}

void SquarePattern::start()
{
	_completeTime = 5.5f;
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 screenCenter = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	_spawnInfo[0].pos = Vec2(screenCenter.x - suqareWidth, screenCenter.y + suqareHeight);
	_spawnInfo[1].pos = Vec2(screenCenter.x + suqareWidth, screenCenter.y + suqareHeight);
	_spawnInfo[2].pos = Vec2(screenCenter.x + suqareWidth, screenCenter.y - suqareHeight);
	_spawnInfo[3].pos = Vec2(screenCenter.x - suqareWidth, screenCenter.y - suqareHeight);

	_spawnInfo[0].direction = Vec2::UNIT_X;
	_spawnInfo[1].direction = -Vec2::UNIT_Y;
	_spawnInfo[2].direction = -Vec2::UNIT_X;
	_spawnInfo[3].direction = Vec2::UNIT_Y;

	std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
	std::shuffle(_randomIndex, _randomIndex + 4, rng);
}

void SquarePattern::update(float dt)
{
	_timer += dt;
	_completeTimer += dt;
	if (_spawnIndex < 4 && _timer >= _spawnInterval)
	{
		_timer = 0;
		int randomIndex = _randomIndex[_spawnIndex++];
		Vec2 pos = _spawnInfo[randomIndex].pos;
		Vec2 dir = _spawnInfo[randomIndex].direction;
		_spawnInfo[randomIndex].arrow = ArrowPool::getInstance().Pop(pos, dir, 0.001f);
	}
	else if (_spawnIndex >= 4 && _timer >= _arrowInterval) 
	{
		_timer = 0;
		for (int i =0 ; i < 4; i++)
		{
			Vec2 pos = _spawnInfo[i].pos;
			Vec2 dir = _spawnInfo[i].direction;
			ArrowPool::getInstance().Pop(pos, dir, _arrowSpeed);
		}
	}
}

void SquarePattern::reset()
{
	SectorPattern sector(1);
	sector.start();

	for (auto& spawner : _spawnInfo) 
	{
		ArrowPool::getInstance().Push(spawner.arrow);
	}
}

bool SquarePattern::isCompleted()
{
	return _completeTimer >= _completeTime;
}
