#pragma once 

#ifndef ENTITY_H
#define ENTITY_H
#endif

#include <SFML\Graphics.hpp> 
#include "..\Constants\Constants.h"

class Entity
{
public:
	Entity(sf::RenderWindow*, sf::RenderTexture*);
	virtual ~Entity();
	virtual bool init() = 0; 
	virtual void render() const = 0; 
	virtual void update(const sf::Time&) = 0;
	virtual void handleEvents(sf::Event&, const sf::Time&) = 0;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getPosition() const;
protected: 
	sf::RenderWindow* window_ = nullptr; 
	sf::RenderTexture* renderTexture_ = nullptr;
	sf::Texture texture_; 
	sf::Sprite sprite_;
};