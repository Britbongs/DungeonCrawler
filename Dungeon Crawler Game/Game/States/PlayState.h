#ifndef PLAYSTATE_H
#define PLAYSTATE_H


#include <SFML\Graphics.hpp>
#include <vector>
#include <assert.h>
#include "GameStates.h"
#include "..\Entities\Entities.h"
#include "..\Map\Map.h"
#include "..\Map\MapLoader.h"
#include "..\Constants\Constants.h"
#include "..\Utils\Camera.h"
#include "..\GUI\GUI.h"


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
private: 
	std::vector<Entity*> entities_;
	Map* map_ = nullptr; 
	MapLoader* mapLoader_ = nullptr;
	Camera* camera_ = nullptr;
	Player* player_ = nullptr;
	GUI* gui_ = nullptr;
};
#endif