#ifndef TILEDMAP_H
#define TILEDMAP_H

#include <SFML\Graphics.hpp> 
#include "..\Utils\MTileMap.h"
#include "..\Constants\Constants.h"

class TiledMap : 
	public sf::Transformable, public sf::Drawable
{
	typedef MTileMap Map; 
public:
	TiledMap();
	TiledMap(Map*); //Param: Pointer to a tmx map
	~TiledMap();
	//update functions
	bool initaliseMap();
	//accessor functions
	int getTileWidth() const; 
	int getTileHeight() const;
	void setTMXFile(Map*);
	bool isPlaceFree(sf::Vector2f) const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool initVertexArrays(); //Setup the vector of vertex arrays
	bool initVertArray(int index); //initialise each individual vertex array
	int getTilesetID(int tileID) const;  //Will return the index of the correct tileset to use for rendering 
	Map* currentTMXMap_ = nullptr; //TMX Map pointer
	vector< sf::VertexArray> renderLayer_; //Used to construct tilemap
	vector<int> firstGID_; //global id of the first tile in each tileset of the map
	vector<int> tileCount_; //total number of tiles in each tileset of the map
	sf::Vector2u mapBounds_; //Size of the map in tiles 
	sf::Vector2u tileSize_; //Dimensions of the tile
	vector< sf::Texture> tileset_; //texture used for the tileset
	sf::Texture tempText; 

};
#endif