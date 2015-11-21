#include "MathUtils.h"

MathUtils::MathUtils()
{
}

MathUtils::~MathUtils()
{
}

float MathUtils::LinearTweenPosition(float currentTime, float startValue, float delta, float duration)
{
	return( delta * (currentTime  / duration )+ startValue);
} 
