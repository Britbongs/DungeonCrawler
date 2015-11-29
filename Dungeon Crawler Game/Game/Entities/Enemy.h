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
	Enemy(int, sf::Vector2i, Map*, const std::string&, sf::RenderWindow*, sf::RenderTexture*);
	~Enemy();
	bool init();
	void render() const;
	void update(const sf::Time&);
	std::string getEnemyType() const;
	void takeDamage(int);
	bool isAlive() const;
	void setCombatTarget(Entity* e = nullptr);
	void removeTarget();
	bool doesHaveTarget() const;
	int getEnemyID() const; 
private:
	void setTextureRect();
	bool loadTextureRects();
	bool loadSpriteTexture();
	void setTextPos();
	struct TextureRects{ sf::IntRect* rects; };
private:
	const int TILESIZE;
	TextureRects rects;
	int subImageCount_ = 0;
	std::string type_;
	sf::Font font_;
	sf::Text text_;
	Entity* target_;
	int state_;
	int health_;
	int id_;
	bool isInCombat_;
};

#endif