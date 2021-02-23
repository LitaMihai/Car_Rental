#include "RegistrationState.h"

void RegistrationState::initVariables()
{
	this->emailInput = "";
	this->emailText.setString("");
	this->passwordInput = "";
	this->passwordText.setString("");
	this->passwordAsterisk = "";
	this->confirmPasswordInput = "";
	this->confirmPasswordText.setString("");
	this->confirmPasswordAsterisk = "";

	this->failedConfirmation.setString("");
	this->numberOfFailedPasswordConfirmations = 1;
	this->failedConfirmationString = "Password mismatch!!! X";

	this->writeOnEmailText = true;
	this->writeOnPasswordText = false;
	this->writeOnConfirmPasswordText = false;
	this->samePasswords = true;
	this->emptyPassword = true;
	this->accountAlreadyRegistered = true;
	this->emptyEmail = true;

	this->title.setString("");
	this->emailLabel.setString("");
	this->passwordLabel.setString("");
	this->confirmPasswordLabel.setString("");
}

void RegistrationState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Background/bg.png"))
		throw "ERROR::ACCOUTSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	this->background.setTexture(&this->backgroundTexture);
}

void RegistrationState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void RegistrationState::initText()
{
	//Title
	this->title.setFont(this->font);
	this->title.setFillColor(sf::Color::White);
	this->title.setCharacterSize(52);
	this->title.setPosition(sf::Vector2f(300, 100));
	this->title.setString("Car Rental");

	//Email Label
	this->emailLabel.setFont(this->font);
	this->emailLabel.setFillColor(sf::Color::White);
	this->emailLabel.setCharacterSize(32);
	this->emailLabel.setPosition(sf::Vector2f(20, 250));
	this->emailLabel.setString("Email");

	//Email Text
	this->emailText.setFont(this->font);
	this->emailText.setFillColor(sf::Color::Black);
	this->emailText.setCharacterSize(28);
	this->emailText.setPosition(sf::Vector2f(255, 253));

	//Password Label
	this->passwordLabel.setFont(this->font);
	this->passwordLabel.setFillColor(sf::Color::White);
	this->passwordLabel.setCharacterSize(32);
	this->passwordLabel.setPosition(sf::Vector2f(20, 320));
	this->passwordLabel.setString("Password");

	//Password Text
	this->passwordText.setFont(this->font);
	this->passwordText.setFillColor(sf::Color::Black);
	this->passwordText.setCharacterSize(28);
	this->passwordText.setPosition(sf::Vector2f(255, 323));

	//Confirm Password Label
	this->confirmPasswordLabel.setFont(this->font);
	this->confirmPasswordLabel.setFillColor(sf::Color::White);
	this->confirmPasswordLabel.setCharacterSize(32);
	this->confirmPasswordLabel.setPosition(sf::Vector2f(20, 390));
	this->confirmPasswordLabel.setString("Confirm Password");

	//Confirm Password text
	this->confirmPasswordText.setFont(this->font);
	this->confirmPasswordText.setFillColor(sf::Color::Black);
	this->confirmPasswordText.setCharacterSize(28);
	this->confirmPasswordText.setPosition(sf::Vector2f(255, 393));

	//Wrong Password Confirmation
	this->failedConfirmation.setFont(this->font);
	this->failedConfirmation.setFillColor(sf::Color::Red);
	this->failedConfirmation.setCharacterSize(32);
	this->failedConfirmation.setPosition(sf::Vector2f(230, 450));

	//Please enter a password
	this->pleaseEnterAPassword.setFont(this->font);
	this->pleaseEnterAPassword.setFillColor(sf::Color::Red);
	this->pleaseEnterAPassword.setCharacterSize(32);
	this->pleaseEnterAPassword.setPosition(sf::Vector2f(230, 450));

	//Please enter an email
	this->pleaseEnterAnEmail.setFont(this->font);
	this->pleaseEnterAnEmail.setFillColor(sf::Color::Red);
	this->pleaseEnterAnEmail.setCharacterSize(32);
	this->pleaseEnterAnEmail.setPosition(sf::Vector2f(230, 450));

	//Account already registered string
	this->accountAlreadyRegisteredString.setFont(this->font);
	this->accountAlreadyRegisteredString.setFillColor(sf::Color::Red);
	this->accountAlreadyRegisteredString.setCharacterSize(32);
	this->accountAlreadyRegisteredString.setPosition(sf::Vector2f(230, 450));
}

void RegistrationState::initButtons()
{
	this->buttons["CONNECT"] = new Button(
		50.f, 490.f, 175.f, 70.f,
		&this->font,
		"Register", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["BACK"] = new Button(
		620.f, 490.f, 100.f, 70.f,
		&this->font,
		"Back", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["EMAIL"] = new Button(
		250.f, 255.f, 500.f, 35.f,
		&this->font,
		"", 50,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

	this->buttons["PASSWORD"] = new Button(
		250.f, 325.f, 500.f, 35.f,
		&this->font,
		"", 50,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

	this->buttons["CONFIRMPASSWORD"] = new Button(
		250.f, 395.f, 500.f, 35.f,
		&this->font,
		"", 50,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);
}

bool RegistrationState::verifPasswords(std::string pass1, std::string pass2)
{
	if (pass1.compare(pass2) == 0)
		return true;
	else
		return false;
}

bool RegistrationState::addAccount(std::string email, std::string password)
{
	if (this->accountDataBase->isConnected()) {
		MYSQL_RES* result;
		MYSQL_ROW row = NULL;

		std::string query = "INSERT INTO `users`(`ID`, `Email`, `Password`) VALUES (0, '" + email + "'," + password + ")"; //the query

		mysql_query(this->accountDataBase->getConnection(), query.c_str()); //send the query

		result = mysql_store_result(this->accountDataBase->getConnection()); //store the result

		if (result)
			row = mysql_fetch_row(result);
		mysql_free_result(result);

		if (!row)
			return true;
		else
			return false;
	}
	else return false;
}

bool RegistrationState::isRegistrated(std::string email)
{
	if (this->accountDataBase->isConnected()) {
		MYSQL_RES* result;
		MYSQL_ROW row = NULL;
		int query_rez;
		bool ok = false;

		std::string query = "SELECT `Email` FROM `users` WHERE `Email` = '" + email + "'"; //the query

		query_rez = mysql_query(this->accountDataBase->getConnection(), query.c_str()); //send the query

		result = mysql_store_result(this->accountDataBase->getConnection()); //store the result

		if (result)
			row = mysql_fetch_row(result);
		mysql_free_result(result);

		if (row)
			return true;
		else
			return false;
	}
	else return false;
}

RegistrationState::RegistrationState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* accountDataBase) : State(window, states), accountDataBase(accountDataBase)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initButtons();
}

RegistrationState::~RegistrationState() 
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;
}

void RegistrationState::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed)
			this->window->close();

		if (this->event.type == sf::Event::TextEntered) {
			if (writeOnEmailText) {
				if (std::isprint(this->event.text.unicode))
					this->emailInput += this->event.text.unicode;
			}
			else if (writeOnPasswordText) {
				if (std::isprint(this->event.text.unicode)) {
					this->passwordInput += this->event.text.unicode;
					this->passwordAsterisk += '*';
				}
			}
			else if(writeOnConfirmPasswordText){
				if (std::isprint(this->event.text.unicode)) {
					this->confirmPasswordInput += this->event.text.unicode;
					this->confirmPasswordAsterisk += '*';
				}
			}	
		}
			
		if (this->event.type == sf::Event::KeyPressed) {
			if (this->event.key.code == sf::Keyboard::BackSpace) {

				if (writeOnEmailText) {
					if (!emailInput.empty())
						this->emailInput.pop_back();
				}

				else if (writeOnPasswordText) {
					if (!passwordInput.empty()) {
						this->passwordInput.pop_back();
						this->passwordAsterisk.pop_back();
					}
				}
					
				else if (writeOnConfirmPasswordText) {
					if (!confirmPasswordInput.empty()) {
						this->confirmPasswordInput.pop_back();
						this->confirmPasswordAsterisk.pop_back();
					}
				}
			}

			if (this->event.key.code == sf::Keyboard::Tab) {
				if (writeOnEmailText) {
					this->writeOnEmailText = false;
					this->writeOnPasswordText = true;
					this->writeOnConfirmPasswordText = false;
				}
				else if (writeOnPasswordText) {
					this->writeOnEmailText = false;
					this->writeOnPasswordText = false;
					this->writeOnConfirmPasswordText = true;
				}
				else if(writeOnConfirmPasswordText){
					this->writeOnEmailText = true;
					this->writeOnPasswordText = false;
					this->writeOnConfirmPasswordText = false;
				}
			}
		}
	}
}

void RegistrationState::updateCursor()
{
	this->text_effect_time += this->clock.restart();
	if (this->text_effect_time >= sf::seconds(0.5f)) {
		this->show_cursor = !this->show_cursor;
		this->text_effect_time = sf::Time::Zero;
	}
	
	else if (writeOnEmailText) {
		this->emailText.setString(emailInput + (show_cursor ? '|' : ' '));
		this->passwordText.setString(passwordAsterisk);
		this->confirmPasswordText.setString(confirmPasswordAsterisk);
	}

	else if(writeOnPasswordText){
		this->emailText.setString(emailInput);
		this->passwordText.setString(passwordAsterisk + (show_cursor ? '|' : ' '));
		this->confirmPasswordText.setString(confirmPasswordAsterisk);
	}
	
	else if(writeOnConfirmPasswordText){
		this->emailText.setString(emailInput);
		this->passwordText.setString(passwordAsterisk);
		this->confirmPasswordText.setString(confirmPasswordAsterisk + (show_cursor ? '|' : ' '));
	}
}

void RegistrationState::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);

	//Confirm button(register) -> create the account
	if (this->buttons["CONNECT"]->isPressed()) {
		if (!emailInput.empty()) {
			this->emptyEmail = false;
			if (!passwordInput.empty()) {
				if (!this->isRegistrated(this->emailInput)) {
					if (this->verifPasswords(passwordInput, confirmPasswordInput)) {
						std::cout << "\nPasswords are the same!";
						this->failedConfirmation.setString("");
						this->numberOfFailedPasswordConfirmations = 0;

						//Adding the account in the database.
						if (this->addAccount(this->emailInput, this->passwordInput))
							std::cout << "Account registrated!";
						else
							std::cout << "Account isn't registrared!";

						//Previous state
						this->states->top()->endState();
					}
					else {
						std::cout << "\nPasswords mismatch!";
						this->samePasswords = false;
						this->failedConfirmation.setString(failedConfirmationString + std::to_string(numberOfFailedPasswordConfirmations));
						this->accountAlreadyRegisteredString.setString("");
						numberOfFailedPasswordConfirmations++;
					}
				}
				else {
					this->accountAlreadyRegistered = true;
					this->accountAlreadyRegisteredString.setString("Email Used!!!");
					this->failedConfirmation.setString("");
				}
			}
			else {
				std::cout << "Please enter a password and confirm it!";
				this->failedConfirmation.setString("");
				this->pleaseEnterAPassword.setString("Please enter a password!");
				this->emptyPassword = true;
			}
		}
		else {
			this->failedConfirmation.setString("");
			this->pleaseEnterAnEmail.setString("Please enter an email!");
			this->emptyEmail = true;
		}
	}
	//Previous state
	if (this->buttons["BACK"]->isPressed()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->states->top()->endState();
	}
		
	//Select the email box
	if (this->buttons["EMAIL"]->isPressed()) {
		this->writeOnEmailText = true;
		this->writeOnPasswordText = false;
		this->writeOnConfirmPasswordText = false;
	}
		
	//Select the password box
	if (this->buttons["PASSWORD"]->isPressed()) {
		this->writeOnEmailText = false;
		this->writeOnPasswordText = true;
		this->writeOnConfirmPasswordText = false;
	}

	//Select the confirm-password box
	if (this->buttons["CONFIRMPASSWORD"]->isPressed()) {
		this->writeOnEmailText = false;
		this->writeOnPasswordText = false;
		this->writeOnConfirmPasswordText = true;
	}
}

void RegistrationState::update()
{
	this->updateSFMLEvents();
	this->updateCursor();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void RegistrationState::renderText(sf::RenderTarget* target)
{
	target->draw(this->title);
	target->draw(this->emailLabel);
	target->draw(this->passwordLabel);
	target->draw(this->confirmPasswordLabel);
}

void RegistrationState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
}

void RegistrationState::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	this->renderButtons(target);
	this->renderText(target);
	target->draw(this->emailText);
	target->draw(this->passwordText);
	target->draw(this->confirmPasswordText);
	if (!this->samePasswords)
		target->draw(this->failedConfirmation);
	if (!this->emptyPassword)
		target->draw(this->pleaseEnterAPassword);
	if (this->accountAlreadyRegistered)
		target->draw(this->accountAlreadyRegisteredString);
	if (!this->emptyEmail)
		target->draw(this->pleaseEnterAnEmail);
	this->window->display();
}