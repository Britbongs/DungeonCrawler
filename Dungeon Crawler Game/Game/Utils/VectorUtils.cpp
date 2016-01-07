#include "VectorUtils.h"

sf::Vector2f subtractVector(sf::Vector2f a, sf::Vector2f b)
{
	return(sf::Vector2f(a.x - b.x, a.y - b.y));
}

sf::Vector2f addVector(sf::Vector2f a, sf::Vector2f b)
{
	return(sf::Vector2f(a.x + b.x, a.y + b.y));
}

double dotProduct(sf::Vector2f a, sf::Vector2f b)
{//Returns the dot product of two vectors
	return((a.x * b.x) + (a.y * b.y));
}

sf::Vector2f normalize(sf::Vector2f a)
{//normalises a vector and returns the normalised product
	float length = static_cast<float> (sqrt(powf(a.x, 2) + powf(a.y, 2)));

	return(sf::Vector2f(a.x / length, a.y / length));
}