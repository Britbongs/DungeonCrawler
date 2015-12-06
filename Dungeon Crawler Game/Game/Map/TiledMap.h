#ifndef TILEDMAP_H
#define TILEDMAP_H

#include <SFML\Graphics.hpp> 
#include "..\Utils\TMXMap.h"

class TiledMap : 
	public sf::Transformable, sf::Drawable
{
	typedef MTileMap Map; 
public:
	TiledMap(Map*);
	bool initaliseMap();
	~TiledMap();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	Map* currentMap; 
	sf::VertexArray* vertexArr_; //Used to construct tilemap
	sf::Vector2u mapBounds_; 
	sf::Texture tileset;
};
#endif