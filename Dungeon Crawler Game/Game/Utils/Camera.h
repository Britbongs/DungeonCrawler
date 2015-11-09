#pragma once 
#include <SFML\Graphics.hpp> 
#include <iostream>
#include <assert.h>
#include "..\Entities\Entities.h"
#include "..\Constants\Constants.h"	

class Camera
{
public: 
	Camera(sf::Vector2u, sf::RenderTexture*);
	~Camera();
	void translate(const sf::Vector2f&);
private: 
	const int VIEW_WIDTH, VIEW_HEIGHT;
	const sf::Vector2u MAP_BOUNDS;
	const int TILESIZE;
	sf::RenderTexture* renderTexture_ = nullptr;
};