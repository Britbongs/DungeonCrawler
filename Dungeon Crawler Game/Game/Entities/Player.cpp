#include "Player.h"	

Player::Player()
	: Entity(sf::Quads, 4)
{
	
	this->setVertexLocalPosition(0, sf::Vector2f(0.f, 0.f));
	this->setVertexLocalPosition(1, sf::Vector2f(1.f, 0.f));
	this->setVertexLocalPosition(2, sf::Vector2f(1.f, 1.f));
	this->setVertexLocalPosition(3, sf::Vector2f(0.f, 1.f));

	for (int i(0); i < this->getVertexCount(); ++i)
		this->setVertexColour(i, sf::Color::Green);
}