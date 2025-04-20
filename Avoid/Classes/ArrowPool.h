#pragma once
#include <stack>
#include "Arrow.h"

class ArrowPool
{
public:
	ArrowPool(int _count);
	~ArrowPool();

	static Arrow* Pop();
	static void Push(Arrow* _arrow);

private:
	static void createPool(int _count);
	static void releasePool();

	static std::stack<Arrow*> pool;
};

