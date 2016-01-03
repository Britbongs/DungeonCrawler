#include "State.h"

State::State(int STATE_ID, sf::RenderWindow* window, sf::RenderTexture* renderTexture) : STATE_ID(STATE_ID), window_(window), renderTexture_(renderTexture)
{

}

State::~State()
{
	deinit();
}

int State::getStateID() const
{
	return(STATE_ID);
}

void State::deinit()
{

}