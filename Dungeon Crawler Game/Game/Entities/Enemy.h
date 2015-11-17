#ifndef ENEMY_H
#define ENEMY_H
#include <fstream>
#include "Entity.h"
#include "..\Map\Map.h"
#include "..\Constants\Constants.h"

using namespace gconsts::AITextureRectangles;

class Enemy :
	public Entity
{
public:
	Enemy(sf::Vector2i, Map*, const std::string&, sf::RenderWindow*, sf::RenderTexture*);
	~Enemy();
	bool init();
	void render() const;
	void update(const sf::Time&);
	std::string getEnemyType() const;
	void takeDamage(int);
private:
	void setTextureRect();
	bool loadTextureRects();
	bool loadSpriteTexture();
	struct TextureRects{ sf::IntRect* rects; };
private:
	const int TILESIZE;
	TextureRects rects;
	int subImageCount_ = 0;
	std::string type_;
	sf::Font font_; 
	sf::Text text_;
	int state_;
	int health_;
};

#endif