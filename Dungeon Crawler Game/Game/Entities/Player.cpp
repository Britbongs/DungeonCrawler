#include "Player.h"

Player::Player(sf::Vector2i startPosition, Map* map, sf::RenderWindow* window, sf::RenderTexture* renderTexture) : map_(map), TILESIZE(gconsts::Gameplay::TILESIZE), Entity(window, renderTexture)
{
	//shape_.setPosition((float)startPosition.x * TILESIZE, (float)startPosition.y * TILESIZE);
	sprite_.setPosition((float)startPosition.x * TILESIZE, (float)startPosition.y * TILESIZE);
}

Player::~Player()
{

}

bool Player::init()
{
	shape_.setSize(sf::Vector2f(64.f, 64.f));
	shape_.setFillColor(sf::Color::Green);
	if (!texture_.loadFromFile(gconsts::Assets::PLAYER_TEXTURE_LOCATION))
		return(false);

	if (!loadTextureRect())
		return(false);

	sprite_.setTexture(texture_);
	sprite_.setScale(2.f, 2.f);

	shape_.setPosition(sprite_.getPosition());

	setTextureRect(W_DOWN);
	return(true);
}

bool Player::loadTextureRect()
{
	std::ifstream fromFile;

	fromFile.open(gconsts::Assets::PLAYER_TEXTURE_RECTS, std::ios::in);

	if (fromFile.fail())
	{
		printf("Failed to open Player Texture Rects file!");
		return(false);
	}
	else
	{
		fromFile >> txtRects_.down.left;
		fromFile >> txtRects_.down.top;
		fromFile >> txtRects_.down.width;
		fromFile >> txtRects_.down.height;

		fromFile >> txtRects_.up.left;
		fromFile >> txtRects_.up.top;
		fromFile >> txtRects_.up.width;
		fromFile >> txtRects_.up.height;

		fromFile >> txtRects_.left.left;
		fromFile >> txtRects_.left.top;
		fromFile >> txtRects_.left.width;
		fromFile >> txtRects_.left.height;

		fromFile >> txtRects_.right.left;
		fromFile >> txtRects_.right.top;
		fromFile >> txtRects_.right.width;
		fromFile >> txtRects_.right.height;

		fromFile >> txtRects_.attackDown.left;
		fromFile >> txtRects_.attackDown.top;
		fromFile >> txtRects_.attackDown.width;
		fromFile >> txtRects_.attackDown.height;

		fromFile >> txtRects_.attackUp.left;
		fromFile >> txtRects_.attackUp.top;
		fromFile >> txtRects_.attackUp.width;
		fromFile >> txtRects_.attackUp.height;

		fromFile >> txtRects_.attackLeft.left;
		fromFile >> txtRects_.attackLeft.top;
		fromFile >> txtRects_.attackLeft.width;
		fromFile >> txtRects_.attackLeft.height;

		fromFile >> txtRects_.attackRight.left;
		fromFile >> txtRects_.attackRight.top;
		fromFile >> txtRects_.attackRight.width;
		fromFile >> txtRects_.attackRight.height;

	}
	fromFile.close();
	return(true);
}

void Player::render() const
{
	renderTexture_->draw(sprite_);
}

void Player::update(const sf::Time& delta)
{
	
}

void Player::handleEvents(sf::Event& evnt, const sf::Time& delta)
{
	if (evnt.type == sf::Event::KeyPressed)
	{
		sf::FloatRect collider = sprite_.getGlobalBounds();
		if (evnt.key.code == sf::Keyboard::D || evnt.key.code == sf::Keyboard::Right)
		{
			collider.left += TILESIZE;
			if (map_->isPlaceFree(collider))
				sprite_.move(TILESIZE, 0);
			setTextureRect(W_RIGHT);
		}
		if (evnt.key.code == sf::Keyboard::A || evnt.key.code == sf::Keyboard::Left)
		{
			collider.left -= TILESIZE;
			if (map_->isPlaceFree(collider))
				sprite_.move(-TILESIZE, 0);
			setTextureRect(W_LEFT);
		}
		if (evnt.key.code == sf::Keyboard::W || evnt.key.code == sf::Keyboard::Up)
		{
			collider.top -= TILESIZE;
			if (map_->isPlaceFree(collider))
				sprite_.move(0, -TILESIZE);
			setTextureRect(W_UP);
		}
		if (evnt.key.code == sf::Keyboard::S || evnt.key.code == sf::Keyboard::Down)
		{
			collider.top += TILESIZE;
			if (map_->isPlaceFree(collider))
				sprite_.move(0, TILESIZE);
			setTextureRect(W_DOWN);
		}
	}

}

void Player::setTextureRect(int state)
{
	if (state == W_DOWN)
		sprite_.setTextureRect(txtRects_.down);

	if (state == W_UP)
		sprite_.setTextureRect(txtRects_.up);

	if (state == W_LEFT)
		sprite_.setTextureRect(txtRects_.left);

	if (state == W_RIGHT)
		sprite_.setTextureRect(txtRects_.right);

	if (state == A_DOWN)
		sprite_.setTextureRect(txtRects_.attackDown);

	if (state == A_UP)
		sprite_.setTextureRect(txtRects_.attackUp);

	if (state == A_LEFT)
		sprite_.setTextureRect(txtRects_.attackLeft);

	if (state == A_RIGHT)
		sprite_.setTextureRect(txtRects_.attackRight);
}