#include "random.hpp"

float randSeed(float seed, float min, float max)
{
	float _sin = sinf(seed)*10000.f;
	
	_sin = _sin - floorf(_sin);
	
	return _sin * (max - min) + min;
}

int randSeed(float seed, int min, int max)
{
	float _sin = sinf(seed)*10000.f;
	
	_sin = _sin - floorf(_sin);
	
	return _sin * (max - min) + min;
}