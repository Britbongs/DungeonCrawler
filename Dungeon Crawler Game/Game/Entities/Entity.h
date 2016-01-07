#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp> 
#include <assert.h>
#include "..\Utils\VectorUtils.h"

class Entity
	: public sf::Drawable, public sf::Transformable
{
public:
	Entity();
	Entity(sf::PrimitiveType, int vertexCount);
	void setVertexLocalPosition(int, sf::Vector2f);
	void setVertexColour(int, sf::Color);
	void setVertexTextureCoords(int, sf::Vector2f);
	void setTexture(sf::Texture*);
	void resizeArray(int);
	void setPrimitiveType(sf::PrimitiveType);
	int getVertexCount() const;
	sf::Vector2f getVertexGlobalPosition(int) const;
	sf::Vector2f getNormal(int, int) const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	sf::VertexArray vertices_;
	sf::Texture* texture_;
};
#endif