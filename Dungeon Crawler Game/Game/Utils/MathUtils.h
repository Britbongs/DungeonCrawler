
#ifndef MATH_H
#define MATH_H 
#include <SFML\Graphics.hpp>

class MathUtils
{
public:
	MathUtils();
	~MathUtils();
	//Param: current time, start value, change in value, duration of the linearTween
	static float LinearTweenPosition(float, float, float, float); 
	static float DotProduct(sf::Vector2f, sf::Vector2f);
};



#endif 