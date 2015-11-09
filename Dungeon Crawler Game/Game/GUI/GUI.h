#pragma once

#ifndef GUI_H
#define GUI_H
#endif

#include <SFML\Graphics.hpp> 
#include "..\Constants\Constants.h"

class GUI
{
public: 
	GUI(); 
	~GUI();
	bool init(sf::RenderTexture&);
	void render(sf::RenderTexture&);
private: 
	sf::View createGUIView() const;
private: 
	const int GUI_X, GUI_WIDTH, GUI_HEIGHT, WINDOW_WIDTH;
	sf::Texture guiPaneTexture_;
	sf::Sprite guiPaneSprite_;
};