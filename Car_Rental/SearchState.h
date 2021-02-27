#pragma once

#include "State.h"
#include "Button.h"

class SearchState : public State
{
private:
	//Variables
	sf::RenderWindow* prevWindow;
	sf::RenderWindow* window;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;

	std::map<std::string, Button*> buttons;
	std::map<std::string, Button*> make;
	std::map<std::string, Button*> model;

	sf::Event event;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::RectangleShape linie[4];

	sf::Image icon;

	sf::View makeView;
	sf::View principalView;

	//Functions
	void initWindow(sf::RenderWindow* window);
	void initView();
	void initBackground();
	void initLines();
	void initFonts();
	void initText();
	void initButtons();
	void initMake();
	void initModel();

public:
	//Constructor-Destructor
	SearchState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* accountDataBase);
	virtual ~SearchState();

	//Functions
	void updateSFMLEvents();
	void updateButtons();
	void update();

	void renderText(sf::RenderTarget* target = NULL);
	void renderLines(sf::RenderTarget* target = NULL);
	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

