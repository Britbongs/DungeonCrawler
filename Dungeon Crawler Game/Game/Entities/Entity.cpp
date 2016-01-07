#include "Entity.h"

Entity::Entity()
	: vertices_(sf::Points, 0), texture_(nullptr)
{

}

Entity::Entity(sf::PrimitiveType type, int vetexCount)
	: vertices_(type, vetexCount), texture_(nullptr)
{

}

void Entity::setVertexLocalPosition(int index, sf::Vector2f position)
{
	assert(index < vertices_.getVertexCount() && index >= 0);
	vertices_[index].position = position;
}

void Entity::setVertexColour(int index, sf::Color colour)
{
	assert(index < vertices_.getVertexCount() && index >= 0);
	vertices_[index].color = colour;
}

void Entity::setVertexTextureCoords(int index, sf::Vector2f position)
{
	assert(index < vertices_.getVertexCount() && index >= 0);
	vertices_[index].texCoords = position;
}

void Entity::setTexture(sf::Texture* p_txt)
{
	texture_ = p_txt;
}

void Entity::resizeArray(int size)
{
	vertices_.resize(size);
}

void Entity::setPrimitiveType(sf::PrimitiveType a)
{
	vertices_.setPrimitiveType(a);
}

int Entity::getVertexCount() const
{
	return vertices_.getVertexCount();
}

sf::Vector2f Entity::getVertexGlobalPosition(int index) const
{
	assert(index < vertices_.getVertexCount() && index >= 0);
	return(getTransform().transformPoint(vertices_[index].position));
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (texture_)
		states.texture = texture_;

	target.draw(vertices_, states);
}

sf::Vector2f Entity::getNormal(int v1, int v2) const
{
	assert(v1 >= 0 && v2 >= 0 && v1 < vertices_.getVertexCount() && v2 < vertices_.getVertexCount());

	sf::Vector2f normal(subtractVector(getVertexGlobalPosition(v1), getVertexGlobalPosition(v2)));

	return(sf::Vector2f(-normal.y, normal.x));
}

sf::FloatRect Entity::getLocalBounds() const
{
	sf::FloatRect localBounds;

	switch (vertices_.getPrimitiveType())
	{
	case sf::Quads:
		localBounds.left = vertices_[0].position.x;
		localBounds.top = vertices_[0].position.y;
		localBounds.width = 1.f;
		localBounds.height = 1.f;
		break;
	case sf::Triangles:
		break;
	}
	return(localBounds);
}

sf::FloatRect Entity::getGlobalBounds() const
{
	return (getTransform().transformRect(getLocalBounds()));
}