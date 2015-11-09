#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#endif

#include <fstream>
#include <SFML\Graphics.hpp> 
#include "Entities.h"
#include "..\Map\Map.h"
#include "..\Constants\Constants.h"

class Player :
	public Entity
{
public:
	Player(sf::Vector2i, Map*, sf::RenderWindow*, sf::RenderTexture*);
	~Player();
	bool init();
	void render() const;
	void update(const sf::Time&);
	void handleEvents(sf::Event&, const sf::Time&);
private:
	bool loadTextureRect();
	void setTextureRect(int);
	struct TextureRects
	{
		sf::IntRect down, up, left, right;
		sf::IntRect  attackDown, attackUp, attackLeft, attackRight;
	};
	TextureRects txtRects_;
	const int W_DOWN = 0, W_UP = 1, W_LEFT = 2, W_RIGHT = 3; 
	const int A_DOWN = 4, A_UP = 5, A_LEFT = 6, A_RIGHT = 7;
	const int TILESIZE;
	Map* map_;
	sf::RectangleShape shape_;
	int state_;
};