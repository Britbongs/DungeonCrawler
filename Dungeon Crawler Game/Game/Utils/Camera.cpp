#include "Camera.h"

Camera::Camera(sf::Vector2u MAP_BOUNDS, sf::RenderTexture* renderTexture) :
MAP_BOUNDS(MAP_BOUNDS), renderTexture_(renderTexture), TILESIZE(gconsts::Gameplay::TILESIZE), VIEW_WIDTH(gconsts::Gameplay::GAME_VIEW_WIDTH), VIEW_HEIGHT(gconsts::Gameplay::GAME_VIEW_HEIGHT)
{

}

Camera::~Camera()
{

}

void Camera::translate(const sf::Vector2f& position)
{
	assert(renderTexture_ != nullptr && MAP_BOUNDS.x > 0 && MAP_BOUNDS.y > 0);
	sf::View view;
	view.setSize(VIEW_WIDTH, VIEW_HEIGHT);
	view.setCenter(sf::Vector2f(position.x, position.y));
	const float gameWidth(gconsts::Gameplay::GAME_VIEW_WIDTH);
	const float windowWidth(gconsts::Window::WIDTH);
	view.setViewport(sf::FloatRect(0, 0,(float)(gameWidth/windowWidth), 1));

	view.setCenter(position);
	renderTexture_->setView(view);


	//TODO Write camera translation to hide black space
}