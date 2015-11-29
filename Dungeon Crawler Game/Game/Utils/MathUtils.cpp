#include "MathUtils.h"

MathUtils::MathUtils()
{
}

MathUtils::~MathUtils()
{
}

float MathUtils::LinearTweenPosition(float currentTime, float startValue, float delta, float duration)
{
	return(delta * (currentTime / duration) + startValue);
}

float MathUtils::DotProduct(sf::Vector2f a, sf::Vector2f b)
{
	return((a.x * b.x) + (a.y * b.y));
}