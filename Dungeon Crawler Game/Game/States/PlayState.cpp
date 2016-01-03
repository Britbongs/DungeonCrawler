#include "PlayState.h"

std::ostream& operator<< (std::ostream& out, const Player& pa){
	return out << pa.getPosition().x << " - " << pa.getPosition().y;
}

std::ostream& operator<< (std::ostream& out, const sf::IntRect& r)
{
	return out << r.left << " - " << r.top << " - " << r.width << " - " << r.height;
}

PlayState::PlayState(int STATE_ID, sf::RenderWindow* window, sf::RenderTexture* renderTexture) :
State(STATE_ID, window, renderTexture), combatActive_(false), isPlayerCombatTurn_(false)
{
	entities_.resize(4);
}

PlayState::~PlayState()
{//Deleting class pointers
	deinit();
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


	tmxMap_.loadMap("res//map.tmx");
	tiledMap_.setTMXFile(&tmxMap_);

	if (!tiledMap_.initaliseMap())
		return (false);


	player_ = new Player(sf::Vector2i(7,3), &tiledMap_, window_, renderTexture_);

	if (player_ == nullptr)
		return(false);

	if (!player_->init())
		return(false);

	/*
	entities_[0] = new Enemy(0, map_->randomFreeTile(), map_, "bat", window_, renderTexture_);
	entities_[1] = new Enemy(1, map_->randomFreeTile(), map_, "bat", window_, renderTexture_);
	entities_[2] = new Enemy(2, map_->randomFreeTile(), map_, "bat", window_, renderTexture_);
	entities_[3] = new Enemy(3, map_->randomFreeTile(), map_, "bat", window_, renderTexture_);
	*/

	for (size_t i(0); i < entities_.size(); ++i)
	{
		if (entities_[i] != nullptr)
		{
			if (!entities_[i]->init())
				return(false);
		}
	}
	
	camera_ = new Camera(sf::Vector2u(tiledMap_.getTileWidth(), tiledMap_.getTileHeight()), renderTexture_);
	sf::View view;
	view.setSize(sf::Vector2f((float)gconsts::Gameplay::GAME_VIEW_WIDTH, (float)gconsts::Gameplay::GAME_VIEW_HEIGHT));
	view.setViewport(sf::FloatRect(0.f, 0.f, view.getSize().x / (float)(gconsts::Window::WIDTH), 1.f));
	renderTexture_->setView(view);

	camera_->translate(player_->getPosition());

	gui_ = new GUI();

	if (!gui_->init(*renderTexture_))
		return(false);


	//TODO split init into smaller functions 

	return(true);
}

void PlayState::render()
{
	//renderTexture_->draw(*map_);
	renderTexture_->draw(tiledMap_);
	gui_->render(*renderTexture_);

	for (size_t i(0); i < entities_.size(); ++i)
	{
		if (entities_[i] != nullptr)
		{

			entities_[i]->render();
		}
	}

	player_->render();
}

void PlayState::update(const sf::Time& delta)
{

	player_->update(delta);
	player_->setTurn(false);
	/* 
	if (player_->hasPlayerTurned())
	{
		for (size_t i(0); i < entities_.size(); ++i)
		{
			if (entities_[i] != nullptr)
			{
				entities_[i]->update(delta);
				if (player_->isAttacking())
					handleCombat();
			}
		}
		player_->setTurn(false);
	}
	*/
	sf::Vector2f playerCentre(player_->getPosition().x + player_->getGlobalBounds().width / 2,
		player_->getPosition().y + player_->getGlobalBounds().height / 2);

	camera_->translate(playerCentre);
}

void PlayState::handleEvents(sf::Event& evnt, const sf::Time& delta)
{
	if (!player_->hasPlayerTurned())
		player_->handleEvents(evnt, delta);
}

void PlayState::handleCombat()
{
	bool playerOkay = player_->isAttacking() && player_->hasPlayerTurned();  //Are the players requirements allowd

	sf::FloatRect attackTile(Utils::intRectToFloatRect(player_->getAttackTileLocation()));

	if (playerOkay)
	{

		bool enemyFound(false);
		int counter(0);

		while (counter < entities_.size() && !enemyFound)
		{
			Enemy* e = static_cast<Enemy*> (entities_[counter]);

			if (e != nullptr)
			{
				if (e->getGlobalBounds().intersects(attackTile) && !e->doesHaveTarget())
				{

					enemyFound = true;
					combatEnemyIndicies.push_back(counter);
					/*
					-Possible bug:
					Player may not be able to attack multiple targets. Re-write this implementation
					when necessary.
					*/
				}
			}

			++counter;
		}
	}

	if (combatEnemyIndicies.size() > 0)
	{
		for (int i(0); i < combatEnemyIndicies.size(); ++i)
		{
			Enemy* e = static_cast<Enemy*> (entities_[combatEnemyIndicies[i]]);

			if (e != nullptr)
			{
				if (e->isAlive() && e->getGlobalBounds().intersects(attackTile))
				{
					e->takeDamage(player_->getAttackDamage());
					std::cout << std::boolalpha << player_->isAttacking() << std::endl;
				}
			}
		}
	}
	player_->endAttackTurn();
}

void PlayState::deinit()
{
	delete mapLoader_;
	delete map_;
	delete camera_;
	delete gui_;
	delete player_;
	for (size_t i(0); i < entities_.size(); ++i)
		delete entities_[i]; //Deleting all entity class pointers in the vector entities_
}