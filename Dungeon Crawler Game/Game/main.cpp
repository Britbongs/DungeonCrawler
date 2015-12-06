#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "GameManager\GameManager.h"
#include "Constants\Constants.h"
#include "Utils\TMXMap.h"

int main(void)
{
	//GameManager game(Const::Window::WINDOW_TITLE, Const::Window::WIDTH, Const::Window::HEIGHT); 
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(384);
	/*
	GameManager game(gconsts::Window::SCREEN_TITLE, gconsts::Window::WIDTH, gconsts::Window::HEIGHT);

	if (game.init())
	{
		game.run();
	}
	else
	{
		system("pause");
		return(-1);
	}*/ 

	
	MTileMap map;

	map.loadMap("res//map.tmx");

	system("pause");
	return(0);

}
