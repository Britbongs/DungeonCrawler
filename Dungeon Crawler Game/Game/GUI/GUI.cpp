#include "GUI.h"

GUI::GUI()
	: GUI_X(-256), GUI_WIDTH(gconsts::Gameplay::GUI_VIEW_WIDTH), GUI_HEIGHT(gconsts::Gameplay::GUI_VIEW_HEIGHT), WINDOW_WIDTH(gconsts::Window::WIDTH)
{

}

GUI::~GUI()
{

}

bool GUI::init(sf::RenderTexture& renderTexture_)
{
	if (!guiPaneTexture_.loadFromFile("res//guipanelbase.png")) //TODO remove hardcoding file location
		return(false);

	guiPaneSprite_.setTexture(guiPaneTexture_);
	guiPaneSprite_.setPosition((float)GUI_X, 0);
	guiPaneSprite_.setScale(2.f, 2.f);

	sf::View guiView = createGUIView();

	renderTexture_.setView(guiView);
}

void GUI::render(sf::RenderTexture& renderTexture)
{
	sf::View guiView = createGUIView();
	sf::View oldView = renderTexture.getView();
	renderTexture.setView(guiView);
	renderTexture.draw(guiPaneSprite_);
	renderTexture.setView(oldView);
}

sf::View GUI::createGUIView() const
{
	sf::View guiView;

	guiView.setSize(GUI_WIDTH, GUI_HEIGHT);
	guiView.setCenter(sf::Vector2f(guiPaneSprite_.getPosition().x + guiView.getSize().x / 2, guiPaneSprite_.getPosition().y + guiView.getSize().y / 2));
	const float viewPortLeft(1 - (float)(GUI_WIDTH) / float(WINDOW_WIDTH)), viewPortWidth((float)(GUI_WIDTH) / (float)(WINDOW_WIDTH));
	guiView.setViewport(sf::FloatRect(viewPortLeft, 0, viewPortWidth, 1));

	return(guiView);
}