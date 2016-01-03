#ifndef STATE_H
#define STATE_H


#include <SFML\Graphics.hpp> 
class State
{
public:
	State(int STATE_ID, sf::RenderWindow*, sf::RenderTexture*);
	virtual ~State();
	virtual bool init() = 0;
	virtual void render() = 0;
	virtual void update(const sf::Time&) = 0;
	virtual void handleEvents(sf::Event&, const sf::Time&) = 0;
	virtual void deinit();
	int getStateID() const;
protected:
	sf::RenderWindow* window_ = nullptr;
	sf::RenderTexture* renderTexture_ = nullptr;
	const int STATE_ID;
};

#endif 