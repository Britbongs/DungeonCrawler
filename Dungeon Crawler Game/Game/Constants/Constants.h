
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML\Graphics.hpp> 
#include <string> 

#define FREE '0'
#define BLOCKED '1'
#define ENEMY '2'

namespace gconsts
{
	namespace Window
	{
		static std::string SCREEN_TITLE("The Dare - INDEV");
		static const int WIDTH(1024);
		static const int HEIGHT(640);
	}

	namespace States
	{
		static const int GAMEPLAY_STATE_ID(1);
	}

	namespace Gameplay
	{
		static const int TILESIZE(64);
	}

	namespace Assets
	{
		static const std::string MAP_LOCATION("res//test.scr");
		static const std::string FONT_LOCATION("res//fonts//seriphim.ttf");
	}
}

#endif