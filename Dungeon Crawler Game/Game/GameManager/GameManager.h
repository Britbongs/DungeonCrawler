#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#endif

#include <SFML\Graphics.hpp> 
#include <iostream> 
#include <iomanip> 
#include <vector> 
#include <sstream>
#include "..\States\GameStates.h"
#include "..\Constants\Constants.h"


class GameManager
{
public:
	GameManager(std::string, int, int); //Param: window title, width, height
	~GameManager();
	bool init();
	void run();
private:
	void fpsCounter(const sf::Time& time);
private: 
	const int WIDTH, HEIGHT;
	sf::RenderWindow window_;
	sf::RenderTexture renderTexture_;
	std::vector<State*>states_;
	std::string WINDOW_TITLE;
	sf::Texture texture;
	int activeState;
	bool isWindowActive_ = true;
	sf::Text fpsText_; 
	sf::Font font_; 
	std::string fpsString_;
	float fps_ = 0.f;

};

