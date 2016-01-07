#ifndef CAMERA_H
#define CAMERA_H
#include <SFML\Graphics.hpp> 
#include <iostream>
#include <assert.h>
#include "..\Constants\Constants.h"	


class Camera
{
public:
	Camera(sf::Vector2u, sf::RenderTexture*);
	~Camera();
private:
};
#endif