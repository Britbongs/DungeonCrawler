#include "Camera.h"

Camera::Camera(sf::Vector2u MAP_BOUNDS, sf::RenderTexture* renderTexture) :
renderTexture_(renderTexture), TILESIZE(gconsts::Gameplay::TILESIZE), VIEW_WIDTH(gconsts::Gameplay::GAME_VIEW_WIDTH), VIEW_HEIGHT(gconsts::Gameplay::GAME_VIEW_HEIGHT)
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
	//view.setViewport(gameView.getViewport());

	bool left(false), right(false), up(false), down(false);
	sf::Vector2f bound(gameView.getCenter());

	if (view.getCenter().x != gameView.getCenter().x)
	{
		if (view.getCenter().x < gameView.getCenter().y)
		{
			left = (view.getCenter().x - GAME_WIDTH / 2) > 0;
			bound.x = view.getSize().x/4;
		}
		else
		{
			right = (view.getCenter().x + GAME_WIDTH / 2) < MAP_BOUNDS.y;
			bound.x = MAP_BOUNDS.x - view.getSize().x / 2;
		}

	}


	if (view.getCenter().y != gameView.getCenter().y)
	{
		if (view.getCenter().y < gameView.getCenter().y)
		{
			up = (view.getCenter().x - GAME_HEIGHT / 2) > 0;
			bound.y = view.getSize().y / 4;
		}
		else
		{
			down = (view.getCenter().y + GAME_HEIGHT / 2) < MAP_BOUNDS.y;
			bound.y = MAP_BOUNDS.y - view.getSize().y / 2;
		}
	}

	sf::Vector2f place;

	left || right ? place.x = position.x : place.x = bound.x;
	up || down ? place.y = position.y : place.y = bound.y;

	view.setCenter(place);
	renderTexture_->setView(view);


	//TODO Write camera translation to hide black space
}