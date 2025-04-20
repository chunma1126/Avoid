#include "ArrowPool.h"
#include "Arrow.h"

std::stack<Arrow*> ArrowPool::pool;

ArrowPool::ArrowPool(int _count)
{
    createPool(_count);
}

ArrowPool::~ArrowPool()
{
	releasePool();
}

Arrow* ArrowPool::Pop()
{
	if (pool.empty())
	{
		createPool(10);
	}

	Arrow* newArrow = pool.top();
	pool.pop();
	newArrow->setVisible(true);

	CCLOG("%d", pool.size());

	return newArrow;
}

void ArrowPool::Push(Arrow* _arrow)
{
	_arrow->setVisible(false);
	_arrow->removeFromParentAndCleanup(false);
	_arrow->setDirectionAndSpeed(Vec2::ZERO , 0);
	

	pool.push(_arrow);
}

void ArrowPool::createPool(int _count)
{
    pool = std::stack<Arrow*>();

    for (int i = 0; i < _count; i++)
	{
		Arrow* arrow = Arrow::create();
		//arrow->retain();
		arrow->setVisible(false);
		arrow->setDirectionAndSpeed(Vec2::ZERO , 0);
		pool.push(arrow);
	}
	
}

void ArrowPool::releasePool()
{
	while (!pool.empty())
	{
		Arrow* arrow = pool.top();
		pool.pop();
		arrow->removeFromParentAndCleanup(true);
	}

}
