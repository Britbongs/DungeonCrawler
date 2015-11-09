#include "Entity.h"

Entity::Entity(sf::RenderWindow* window, sf::RenderTexture* renderTexture) : window_(window), renderTexture_(renderTexture)
{

}

Entity::~Entity()
{

}

sf::FloatRect Entity::getGlobalBounds() const
{
	return(sprite_.getGlobalBounds());
}

sf::Vector2f Entity::getPosition() const
{
	return(sprite_.getPosition());
}