#pragma once

#include "State.h"
#include "Button.h"
#include "RegistrationState.h"
#include "SearchState.h"

class AccountState : public State
{
private:
	//Variables
	std::string emailInput;
	sf::Text emailText;
	std::string passwordInput;
	sf::Text passwordText;
	std::string passwordAsterisk;
	sf::Text wrongAccount;
	std::string wrongAccountString;

	bool write_on_emailText;
	bool accountConnected;

	int numberOfFailedEntries;

	sf::Clock clock;
	sf::Time text_effect_time;

	bool show_cursor;

	bool showPassword;
	sf::Texture showButtonTexture;
	sf::Sprite showButtonSprite;

	sf::Text title;
	sf::Text emailLabel;
	sf::Text passwordLabel;

	sf::Event event;

	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	DbConnection *accountDataBase;

	std::map<std::string, Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initText();
	void initButtons();

	bool verifAccount(std::string email, std::string password);

public:
	//Constructor - Destructor
	AccountState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection *accountDataBase);
	virtual ~AccountState();

	//Functions
	void updateSFMLEvents();
	void updateCursor();
	void updateButtons();
	void update();

	void renderText(sf::RenderTarget* target = NULL);
	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

