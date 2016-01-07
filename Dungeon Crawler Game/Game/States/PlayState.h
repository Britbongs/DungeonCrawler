#ifndef PLAYSTATE_H
#define PLAYSTATE_H


#include <vector>
#include <assert.h>
#include <SFML\Graphics.hpp>
#include "GameStates.h"
#include "..\Map\TiledMap.h"
#include "..\Utils\MTileMap.h"
#include "..\Constants\Constants.h"
#include "..\Utils\Camera.h"
#include "..\Utils\Utils.h"
#include "..\Entities\Player.h"

class PlayState :
	public State
{
public:
	PlayState(int, sf::RenderWindow*, sf::RenderTexture*);//Param: stateID
	~PlayState();
	bool init();
	void render();
	void update(const sf::Time&); 
	void handleEvents(sf::Event&, const sf::Time&);
	void deinit();
private: 
	MTileMap tmxMap_;
	TiledMap tiledMap_;
	Player player_;
};

#endif