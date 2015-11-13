#pragma once
#include <SFML\Graphics.hpp> 
#include <string> 

namespace gconsts
{
	namespace Window
	{
		static std::string SCREEN_TITLE("Dungeon Crawler - INDEV");
		static const int WIDTH(640);
		static const int HEIGHT(480);
	}

	namespace States
	{
		static const int GAMEPLAY_STATE_ID(1);
	}

	namespace Gameplay
	{
		static const int TILESIZE(64);
		static const int GAME_VIEW_WIDTH(512);
		static const int GAME_VIEW_HEIGHT(480);
		static const int GUI_VIEW_WIDTH(128);
		static const int GUI_VIEW_HEIGHT(480);
	}

	namespace Assets
	{
		static const std::string MAP_LOCATION("res//test.scr");
		static const std::string FONT_LOCATION("res//minecraft.ttf");
		static const std::string PLAYER_TEXTURE_LOCATION("res//entities//fighter.png");
		static const std::string PLAYER_TEXTURE_RECTS("res//entities//fighterrects.txt");
	}
}