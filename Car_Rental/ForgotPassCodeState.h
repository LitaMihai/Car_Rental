#ifndef FORGOTPASSCODESTATE_H
#define FORGOTPASSCODESTATE_H

#include "State.h"
#include "Button.h"
#include "ForgotPass_NewPass_State.h"

class ForgotPassCodeState : public State
{
private:
	// Variables
	sf::Event event;

	std::map<std::string, Button*> buttons;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	int *code;

	std::string codeInput;
	sf::Text codeText;
	sf::Text codeLabel;
	sf::Text incorrectCode;
	sf::Text email;
	sf::Text anEmailWasSent;
	sf::Text pleaseEnterTheCodeBelow;
	sf::Text ifIsRegistrated;

	std::string emailString;

	sf::Clock clock;
	sf::Time text_effect_time;
	bool show_cursor;

	// Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initText();
	void initButtons();

	bool codeVerif(std::string codeInput);

public:
	// Constructor - Destructor
	ForgotPassCodeState(sf::RenderWindow* window, std::stack<State*>* states, std::string* emailString, int *code);
	virtual ~ForgotPassCodeState();

	// Functions
	void updateSFMLEvents();
	void updateCursor();
	void updateButtons();
	void update();

	void renderText(sf::RenderTarget* target);
	void renderButtons(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);
};

#endif