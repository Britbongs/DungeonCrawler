#include "GameManager.h"


GameManager::GameManager(std::string WINDOW_TITLE, int WINDOW_WIDTH, int WINDOW_HEIGHT) : WINDOW_TITLE(WINDOW_TITLE), WIDTH(WINDOW_WIDTH), HEIGHT(WINDOW_HEIGHT)
{
	//window_.create(sf::VideoMode(WIDTH, HEIGHT), WINDOW_TITLE, sf::Style::Fullscreen);
	window_.create(sf::VideoMode(WIDTH, HEIGHT), WINDOW_TITLE, sf::Style::Close);
	//window_.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), WINDOW_TITLE, sf::Style::Fullscreen);
	activeState = 0;
}

GameManager::~GameManager()
{
	//Loop through all states in the states_ vector
	for (size_t i(0); i < states_.size(); ++i)
	{//Delete all pointers to classes
		if (states_[i] != nullptr)
			delete states_[i];
	} 

}

bool GameManager::init()
{
	
	window_.setKeyRepeatEnabled(false); 



	//window_.setView(view_);
	//window_.setFramerateLimit(60); Activate on release

	//If the creation of the render texture fails
	if (!renderTexture_.create(window_.getSize().x, window_.getSize().y))
		return(false);//Exit out of initialisation

	if (!font_.loadFromFile(gconsts::Assets::FONT_LOCATION))
		return(false); //If loading the font for the FPS counter fails
	
	fpsText_.setFont(font_); //initialise the fpsText with a font
	fpsText_.setCharacterSize(16); //Set it's character size
	fpsText_.setColor(sf::Color::Yellow); //Set it's color to yellow

	states_.push_back(new PlayState(0, &window_, &renderTexture_)); //Add to the states_ list a new state which is initialised with an ID of 0

	for (size_t i(0); i < states_.size(); ++i) //loop through all the states in the game 
		if (!states_[i]->init()) //And call their initialise function, if it returns false
			return(false);	//Exit out of the initialisation
	return(true);
}

void GameManager::run()
{
	sf::Clock clock; //Create a new sfml clock 
	
	while (window_.isOpen())
	{
		sf::Time delta(clock.restart()); //Each loop set delta equal to the amount of elapsed time of 1 loop
		sf::Event evnt;
		while (window_.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				window_.close();
			if (evnt.type == sf::Event::KeyPressed)
				if (evnt.key.code == sf::Keyboard::Escape)
					window_.close();
			if (evnt.type == sf::Event::LostFocus) //If the user has tabbed out
				isWindowActive_ = false; //the window is no longer active
			if (evnt.type == sf::Event::GainedFocus) //If the user has tabbed back in 
				isWindowActive_ = true; //the window is now active again

			if (isWindowActive_)//Only if the window is active
				states_[activeState]->handleEvents(evnt, delta); //Call the handle events of each state
		}

		
		
		if (isWindowActive_)
			states_[activeState]->update(delta);

		

		


		renderTexture_.clear(); //Clear the render texture with the default color of black
		states_[activeState]->render(); //call the render function of each state
		fpsCounter(delta);//Update the FPS counters value
		renderTexture_.draw(fpsText_); //render the fps text 
		renderTexture_.display(); //display thi to the texture


		const sf::Texture& texture = (renderTexture_.getTexture()); //Create a texture with the data from the render texture

		sf::Sprite sprite(texture); //Apply it to a sprite

		window_.clear(); //Clear the window with black
		window_.draw(sprite); //Render the sprite with the renderTexture on it
		window_.display(); //Display it to the window
		

		
		
	}
	
}

void GameManager::fpsCounter(const sf::Time& time)
{
	std::ostringstream os; 
	float tempFPS = 1 / time.asSeconds();  //temporary fps value = 1/elapsed time
	if ((fabs(tempFPS - fps_)) > 10.f) //If the difference between the previous FPS and the current fps is larger than 30.f
	{
		fps_ = tempFPS; //Set the fps float value to temp fps
		os << std::setprecision(4) << fps_; //set the precision for formatting to 4 digits
		fpsString_ = "FPS - " + os.str(); //set the fpsString to "FPS - " concatenated with a temporary string with the fps value
		fpsText_.setString(fpsString_); //set the fpsText (which will be rendered to the screen) to this value
	} 
	//Find the top left position of the screen based on the view's centre-location
	fpsText_.setPosition(sf::Vector2f(renderTexture_.mapPixelToCoords(sf::Vector2i(10, 10))));

} 