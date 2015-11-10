#ifndef MAPLOADER_H
#define MAPLOADER_H 


#include <SFML\Graphics.hpp>
#include <fstream>
#include <assert.h> 
#include <iostream> 

class MapLoader
{
public:
	//Param - File name
	MapLoader(std::string);
	~MapLoader();
	bool loadMap();
	char** getBlockedMap() const;
	int** getTextureMap() const; 
	sf::Vector2u getMapBounds() const;
	sf::Vector2i getPlayerStart() const;
	float getScaleFactor() const;
	int getTileSize() const;
private:
	void printMap() const;
private:
	const std::string FILENAME;
	std::ifstream fileLoader_;
	char** blockedMap_ = nullptr;
	int** textureMap_ = nullptr;
	sf::Vector2u mapBounds_;
	sf::Vector2i playerStart_; 
	float scaleFactor_ = 0.f; 
	int tileSize_ = 0;
};

#endif