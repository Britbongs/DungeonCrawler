#include "Camera.h"

Camera::Camera(sf::Vector2u MAP_BOUNDS, sf::RenderTexture* renderTexture) :
renderTexture_(renderTexture), TILESIZE(gconsts::Gameplay::TILESIZE), VIEW_WIDTH(static_cast<float>( gconsts::Gameplay::GAME_VIEW_WIDTH)), VIEW_HEIGHT(static_cast<float>(gconsts::Gameplay::GAME_VIEW_HEIGHT))
{
	Camera::MAP_BOUNDS = sf::Vector2u(MAP_BOUNDS.x * TILESIZE, MAP_BOUNDS.y * TILESIZE);
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
	const sf::View gameView = renderTexture_->getView();

	view.setViewport(sf::FloatRect(0, 0, ((float)GAME_WIDTH / (float)SCREEN_WIDTH), 1));
	
	sf::Vector2f place(position);

	if (view.getCenter().x - (view.getSize().x / 2) < 0.f)
	{	
		place.x = view.getSize().x / 2;
	}

	if (view.getCenter().x + (view.getSize().x / 2) > MAP_BOUNDS.x)
	{
		place.x = MAP_BOUNDS.x - (view.getSize().x / 2);
	}

	if (view.getCenter().y - (view.getSize().y / 2) < 0.f)
	{
		place.y = view.getSize().y / 2;
	}

	if (view.getCenter().y + (view.getSize().y / 2) > MAP_BOUNDS.y)
	{
		place.y = MAP_BOUNDS.y - (view.getSize().y / 2);
	}

	view.setCenter(place);
	renderTexture_->setView(view);

}