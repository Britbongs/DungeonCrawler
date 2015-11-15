#pragma once

#ifndef MAP_H
#define MAP_H
#endif

#include <SFML\Graphics.hpp> 
#include <assert.h>
#include <iostream>
#include <ctime> 

#define FREE '0'
#define BLOCKED '1'
class Map :
	public sf::Drawable, public sf::Transformable
{
public:
	//Texture map, blocked map, map bounds, tilesize, texture & scale factor
	Map(int**, char**, sf::Vector2u, int, sf::Texture, float);
	~Map();
	bool isPlaceFree(sf::FloatRect);
	bool isContained(sf::FloatRect);
	bool isPointContained(sf::Vector2f) const;
	sf::Vector2u getMapBounds() const;
	sf::Vector2i randomFreeTile() const;
private:
	//TextureMap, mapBounds
	void initVertexArray(int**);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	const int TILESIZE;
	const sf::Vector2u MAP_BOUNDS;
	const sf::Texture TILES;
	char** blockedMap_;
	const float TEXTURE_TILESIZE; //Original texture tile size before being scaled
	sf::VertexArray mapVertexArray_;

};

