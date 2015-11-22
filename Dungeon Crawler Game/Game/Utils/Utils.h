#ifndef UTILS_H
#define UTILS_H 

#include <SFML\Graphics.hpp>

class Utils
{
public:
	Utils();
	~Utils();
	static sf::FloatRect intRectToFloatRect(const sf::IntRect&); //Converts an int rect to a float rect
private:

};



#endif