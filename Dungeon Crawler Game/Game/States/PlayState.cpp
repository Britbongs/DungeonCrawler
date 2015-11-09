#include "PlayState.h"

PlayState::PlayState(int STATE_ID, sf::RenderWindow* window, sf::RenderTexture* renderTexture) : State(STATE_ID, window, renderTexture)
{
	entities_.resize(1);
}

PlayState::~PlayState()
{//Deleting class pointers
	delete mapLoader_;
	delete map_;
	delete camera_;
	delete gui_;
	for (size_t i(0); i < entities_.size(); ++i)
		delete entities_[i]; //Deleting all entity class pointers in the vector entities_
}

bool PlayState::init()
{

	mapLoader_ = new MapLoader(gconsts::Assets::MAP_LOCATION); //initialise the map loader class pointer

	if (!mapLoader_->loadMap()) //If loading the map fails
		return(false); //return false on the initialise function

	sf::Texture tileset;

	if (!tileset.loadFromFile("res//tiles.png"))
		return(false);

	map_ = new Map(mapLoader_->getTextureMap(), mapLoader_->getBlockedMap(), mapLoader_->getMapBounds(), gconsts::Gameplay::TILESIZE, tileset, mapLoader_->getScaleFactor());

	entities_[0] = new Player(mapLoader_->getPlayerStart(), map_, window_, renderTexture_);
	player_ = (Player*)(entities_[0]);

	if (player_ == nullptr)
		return(false);

	for (size_t i(0); i < entities_.size(); ++i)
		if (!entities_[i]->init())
			return(false);

	camera_ = new Camera(mapLoader_->getMapBounds(), renderTexture_);
	sf::View view;
	view.setSize(sf::Vector2f((float)gconsts::Gameplay::GAME_VIEW_WIDTH, (float)gconsts::Gameplay::GAME_VIEW_HEIGHT));
	view.setViewport(sf::FloatRect(0.f, 0.f, view.getSize().x / (float)(gconsts::Window::WIDTH), 1.f));
	renderTexture_->setView(view);

	camera_->translate(player_->getPosition());

	gui_ = new GUI();

	if (!gui_->init(*renderTexture_))
		return(false);

	return(true);
}

void PlayState::render()
{
	renderTexture_->draw(*map_);
	gui_->render(*renderTexture_);
	for (size_t i(0); i < entities_.size(); ++i)
		entities_[i]->render();
	//printf("\n%f - %f", renderTexture_->getView().getSize().x, renderTexture_->getView().getSize().y);
}

void PlayState::update(const sf::Time& delta)
{
	for (size_t i(0); i < entities_.size(); ++i)
		entities_[i]->update(delta);
	sf::Vector2f playerCentre(player_->getPosition().x + player_->getGlobalBounds().width / 2,
		player_->getPosition().y + player_->getGlobalBounds().height / 2);

	camera_->translate(playerCentre);
}

void PlayState::handleEvents(sf::Event& evnt, const sf::Time& delta)
{
	for (size_t i(0); i < entities_.size(); ++i)
		entities_[i]->handleEvents(evnt, delta);
}