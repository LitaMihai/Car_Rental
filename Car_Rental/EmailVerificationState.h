#pragma once

#include "State.h"
#include "Button.h"

class EmailVerificationState : public State
{
private:
	// Variables

	sf::Event event;

	std::string codeInput;
	sf::Text codeText;
	sf::Text codeLabel;

	sf::Text incorrectCode;

	std::map<std::string, Button*> buttons;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	int* code;

	sf::Clock clock;
	sf::Time text_effect_time;
	bool show_cursor;

	bool* continueRegistration;

	// Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initText();
	void initButtons();

	bool codeVerif(std::string codeInput);

public:
	// Constructor - Destructor
	EmailVerificationState(sf::RenderWindow* window, std::stack<State*>* states, int* code, bool* continueRegistration);
	virtual ~EmailVerificationState();

	// Functions
	void updateSFMLEvents();
	void updateCursor();
	void updateButtons();
	void update();

	void renderText(sf::RenderTarget* target);
	void renderButtons(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);
};

