#pragma once

#include "State.h"
#include "Button.h"

class RegistrationState : public State
{
private:
	//Variables
	std::string emailInput;
	sf::Text emailText;
	std::string passwordInput;
	sf::Text passwordText;
	std::string passwordAsterisk;
	std::string confirmPasswordInput;
	sf::Text confirmPasswordText;
	std::string confirmPasswordAsterisk;
	sf::Text failedConfirmation;
	std::string failedConfirmationString;
	sf::Text pleaseEnterAPassword;
	sf::Text accountAlreadyRegisteredString;

	bool writeOnEmailText;
	bool writeOnPasswordText;
	bool writeOnConfirmPasswordText;
	bool samePasswords;
	bool emptyPassword;
	bool accountAlreadyRegistered;

	int numberOfFailedPasswordConfirmations;

	sf::Clock clock;
	sf::Time text_effect_time;
	bool show_cursor;

	sf::Text title;
	sf::Text emailLabel;
	sf::Text passwordLabel;
	sf::Text confirmPasswordLabel;

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

	bool verifPasswords(std::string pass1, std::string pass2);
	bool addAccount(std::string email, std::string password);
	bool isRegistrated(std::string email);
public:
	//Constructor-Destructor
	RegistrationState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection *accountDataBase);
	virtual ~RegistrationState();

	//Functions
	void updateSFMLEvents();
	void updateCursor();
	void updateButtons();
	void update(const float& dt);

	void renderText(sf::RenderTarget* target);
	void renderButtons(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);
};

