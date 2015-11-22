#include "Utils.h"

Utils::Utils()
{
}

Utils::~Utils()
{
}

sf::FloatRect Utils::intRectToFloatRect(const sf::IntRect& a)
{
	sf::FloatRect r; 
	r.left = static_cast<float> (a.left);
	r.top = static_cast<float> (a.top);
	r.width = static_cast<float> (a.width);
	r.height = static_cast<float> (a.height);
	return(r);
}