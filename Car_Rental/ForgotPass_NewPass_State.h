#pragma once

#include "State.h"
#include "Button.h"
#include "SimpleHash.h"

class ForgotPass_NewPass_State : public State
{
private:
	// Variables
	std::string passInput;
	std::string passConfirmationInput;

	std::string* email;

	std::string passAsterisk;
	std::string passConfirmationAsterisk;

	sf::Text passText;
	sf::Text passConfirmationText;

	sf::Text failedConfirmation;

	bool showPassword;
	sf::Texture showButtonTexture;
	sf::Sprite showButtonSprite;

	sf::Clock clock;
	sf::Time text_effect_time;
	bool show_cursor;

	sf::Text title;
	sf::Text passLabel;
	sf::Text passConfirmationLabel;

	sf::Event event;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	DbConnection* accountDataBase;

	std::map<std::string, Button*> buttons;

	bool writeOnPasswordText;
	bool writeOnConfirmPasswordText;

	// Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initText();
	void initButtons();

	bool verifPasswords(std::string pass1, std::string pass2);
	bool changePassword(std::string pass);

public:
	// Constructor - Destructor
	ForgotPass_NewPass_State(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* accountDataBase, std::string* email);
	virtual ~ForgotPass_NewPass_State();

	// Functions
	void updateSFMLEvents();
	void updateCursor();
	void updateButtons();
	void update();

	void renderText(sf::RenderTarget* target);
	void renderButtons(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);
};

