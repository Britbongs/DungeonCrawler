#ifndef TILEDMAP_H
#define TILEDMAP_H

#include <SFML\Graphics.hpp> 
#include "..\Utils\TMXMap.h"

class TiledMap : 
	public sf::Transformable, sf::Drawable
{
	typedef MTileMap Map; 
public:
	TiledMap(Map*); //Param: Pointer to a tmx map
	~TiledMap();
	//update functions
	bool initaliseMap();
	//accessor functions
	int getTileWidth() const; 
	int getTileHeight() const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool initVertexArrays(); //Setup the vector of vertex arrays
	bool initVertArray(int index); //initialise each individual vertex array
	Map* currentTMXMap_ = nullptr; //TMX Map pointer
	vector< sf::VertexArray> renderLayer_; //Used to construct tilemap
	sf::Vector2u mapBounds_; //Size of the map in tiles
	sf::Vector2u tileSize_;
	sf::Texture tileset_; //texture used for the tileset
};
#endif