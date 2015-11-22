#ifndef CAMERA_H
#define CAMERA_H
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
	const float VIEW_WIDTH, VIEW_HEIGHT;
	sf::Vector2u MAP_BOUNDS;
	const int TILESIZE;
	sf::RenderTexture* renderTexture_ = nullptr;
	const int GAME_WIDTH = gconsts::Gameplay::GAME_VIEW_WIDTH;
	const int GAME_HEIGHT = gconsts::Gameplay::GAME_VIEW_HEIGHT;
	const int SCREEN_WIDTH = gconsts::Window::WIDTH;
	const int SCREEN_HEIGHT = gconsts::Window::HEIGHT;
};
#endif