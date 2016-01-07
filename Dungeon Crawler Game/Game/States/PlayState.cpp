#include "PlayState.h"

PlayState::PlayState(int STATE_ID, sf::RenderWindow* window, sf::RenderTexture* renderTexture) :
State(STATE_ID, window, renderTexture)
{
}

PlayState::~PlayState()
{//Deleting class pointers
	deinit();
}

bool PlayState::init()
{
	if (!tmxMap_.loadMap("res//map.tmx"))
		return(false);
	tiledMap_.setTMXFile(&tmxMap_);
	tiledMap_.initaliseMap();

	player_.setScale(64.f, 64.f);
	player_.setPosition(5 * 64, 4 * 64);

	std::cout << player_.getPosition().x << std::endl;
	return(true);
}

void PlayState::render()
{
	renderTexture_->draw(tiledMap_);
	renderTexture_->draw(player_);
}

void PlayState::update(const sf::Time& delta)
{

}

void PlayState::handleEvents(sf::Event& evnt, const sf::Time& delta)
{
}

void PlayState::deinit()
{
}