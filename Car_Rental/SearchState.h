#pragma once

#include "State.h"

class SearchState : public State
{
private:
	//Variables
	sf::RenderWindow* prevWindow;
	sf::RenderWindow* window;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;

	//Functions
	void InitWindow(sf::RenderWindow* window);

public:
	//Constructor-Destructor
	SearchState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* accountDataBase);
	virtual ~SearchState();

	//Functions
	void updateSFMLEvents();
	void updateCursor();
	void updateButtons();
	void update();

	void renderText(sf::RenderTarget* target = NULL);
	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

