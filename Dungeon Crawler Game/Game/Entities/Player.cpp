#include "Player.h"

Player::Player(sf::Vector2i startPosition, Map* map, sf::RenderWindow* window, sf::RenderTexture* renderTexture) :
map_(map), TILESIZE(gconsts::Gameplay::TILESIZE), Entity(window, renderTexture), attackTime(sf::seconds(0)),
attackDamage_(1)
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
	setTextureRect(W_DOWN);
	sprite_.setScale(2.f, 2.f);

	//shape_.setPosition(sprite_.getPosition());

	//setTextureRect(W_DOWN);
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
	if (animationActive_)
	{
		attackTime += delta;
	}


	if (animationActive_ && attackTime > sf::seconds(ANIMTION_LENGTH))
	{
		animationActive_ = false;
		setTextureRect(state_ - 4);
		attackTime = sf::seconds(0);
	}


}

void Player::handleEvents(sf::Event& evnt, const sf::Time& delta)
{

	//Huge if statement below is the movement of the player 
	if (evnt.type == sf::Event::KeyPressed)
	{
		sf::FloatRect collider = sprite_.getGlobalBounds(); //Create a copy collider of the player at his location
		if (!animationActive_)
		{
			if (evnt.key.code == sf::Keyboard::D || evnt.key.code == sf::Keyboard::Right)
			{
				collider.left += TILESIZE; //Move the collider one space right

				if (map_->isPlaceFree(collider))  //if the location this 'copy collider' is in is free
					sprite_.move(TILESIZE, 0); //Move the player to this location 

				setTextureRect(W_RIGHT);
				setTurn(true);
			}
			if (evnt.key.code == sf::Keyboard::A || evnt.key.code == sf::Keyboard::Left)
			{
				collider.left -= TILESIZE;

				if (map_->isPlaceFree(collider))
					sprite_.move(-TILESIZE, 0);

				setTextureRect(W_LEFT);
				setTurn(true);
			}
			if (evnt.key.code == sf::Keyboard::W || evnt.key.code == sf::Keyboard::Up)
			{
				collider.top -= TILESIZE;

				if (map_->isPlaceFree(collider))
					sprite_.move(0, -TILESIZE);

				setTextureRect(W_UP);
				setTurn(true);

			}
			if (evnt.key.code == sf::Keyboard::S || evnt.key.code == sf::Keyboard::Down)
			{
				collider.top += TILESIZE;

				if (map_->isPlaceFree(collider))
					sprite_.move(0, TILESIZE);

				setTextureRect(W_DOWN);
				setTurn(true);

			}
		}

		if (evnt.key.code == sf::Keyboard::X && !animationActive_)
		{
			setTurn(true);
			attacking_ = true;
			animationActive_ = true;
			setTextureRect(state_ + 4);//Switch to the attack animation facing the same direction
		}
	}

}

void Player::setTextureRect(int state)
{
	assert(state <= 7 && state >= 0);

	state_ = state;
	if (!animationActive_)
	{
		if (state == W_DOWN)
			sprite_.setTextureRect(txtRects_.down);

		if (state == W_UP)
			sprite_.setTextureRect(txtRects_.up);

		if (state == W_LEFT)
			sprite_.setTextureRect(txtRects_.left);

		if (state == W_RIGHT)
			sprite_.setTextureRect(txtRects_.right);
	}
	if (animationActive_)
	{
		if (state == A_DOWN)
			sprite_.setTextureRect(txtRects_.attackDown);

		if (state == A_UP)
			sprite_.setTextureRect(txtRects_.attackUp);

		if (state == A_LEFT)
			sprite_.setTextureRect(txtRects_.attackLeft);

		if (state == A_RIGHT)
			sprite_.setTextureRect(txtRects_.attackRight);
	}
}

bool Player::hasPlayerTurned() const
{
	return(endOfTurn_);
}

void Player::setTurn(bool turn)
{
	if (!attacking_)
		endOfTurn_ = turn;
}

bool Player::isAttacking() const
{
	return(attacking_);
}

sf::IntRect Player::getAttackTileLocation() const
{
	sf::IntRect rect(-TILESIZE, -TILESIZE, TILESIZE, TILESIZE);
	if (state_ == A_LEFT)
	{
		rect.left = sprite_.getPosition().x - TILESIZE;
		rect.top = sprite_.getPosition().y;
	}
	if (state_ == A_RIGHT)
	{
		rect.left = sprite_.getPosition().x + TILESIZE;
		rect.top = sprite_.getPosition().y;
	}

	if (state_ == A_UP)
	{
		rect.left = sprite_.getPosition().x;
		rect.top = sprite_.getPosition().y - TILESIZE;
	}

	if (state_ == A_DOWN)
	{
		rect.left = sprite_.getPosition().x;
		rect.top = sprite_.getPosition().y + TILESIZE;
	}

	return(rect);
}

int Player::getAttackDamage() const
{
	return attackDamage_;
}

void Player::endAttackTurn()
{
	attacking_ = false;
}