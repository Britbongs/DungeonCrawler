#include "MathUtils.h"

MathUtils::MathUtils()
{
}

MathUtils::~MathUtils()
{
}

float MathUtils::LinearTween(float currentTime, float startValue, float delta, float duration)
{
	return(currentTime * delta / startValue + duration);
} 
