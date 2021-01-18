#pragma once

#include "State.h"
#include "Application.h"
#include "Button.h"

class AccountState : public State
{
private:
	//Variables
	sf::String emailInput;
	sf::Text emailText;

	sf::Event event;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	
	std::map<std::string, Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initButtons();

public:
	//Constructor - Destructor
	AccountState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~AccountState();

	//Functions
	void updateInput();
	void updateButtons();
	void update(const float& dt);

	void renderText(sf::RenderTarget* target = NULL);
	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

