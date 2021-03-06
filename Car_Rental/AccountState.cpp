#include "AccountState.h"

void AccountState::initVariables()
{	
	this->emailInput = "";
	this->emailText.setString("");
	this->passwordInput = "";
	this->passwordText.setString("");
	this->passwordAsterisk = "";
	
	this->wrongAccount.setString("");
	this->numberOfFailedEntries = 1;
	this->wrongAccountString = "Wrong email or password!!! X";

	this->write_on_emailText = true;
	this->accountConnected = true;

	this->title.setString("");
	this->emailLabel.setString("");
	this->passwordLabel.setString("");
}

void AccountState::initBackground()
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

void AccountState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf")) 
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void AccountState::initText()
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
	this->emailLabel.setPosition(sf::Vector2f(75, 250));
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
	this->passwordLabel.setPosition(sf::Vector2f(75, 350));
	this->passwordLabel.setString("Password");

	//Password Text
	this->passwordText.setFont(this->font);
	this->passwordText.setFillColor(sf::Color::Black);
	this->passwordText.setCharacterSize(28);
	this->passwordText.setPosition(sf::Vector2f(255, 353));

	//Wrong Account Label
	this->wrongAccount.setFont(this->font);
	this->wrongAccount.setFillColor(sf::Color::Red);
	this->wrongAccount.setCharacterSize(32);
	this->wrongAccount.setPosition(sf::Vector2f(230, 450));
}

void AccountState::initButtons()
{
	this->buttons["CONNECT"] = new Button(
		50.f, 490.f, 175.f, 70.f,
		&this->font,
		"Connect", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["EXIT"] = new Button(
		620.f, 490.f, 100.f, 70.f,
		&this->font,
		"Exit", 50,
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
		250.f, 355.f, 500.f, 35.f,
		&this->font,
		"", 50,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

	this->buttons["REGISTER"] = new Button(
		600.f, 20.f, 175.f, 35.f,
		&this->font,
		"Sign Up", 35,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

AccountState::AccountState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection *accountDataBase) : State(window, states), accountDataBase(accountDataBase)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initButtons();
}

AccountState::~AccountState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) 
		delete it->second;
}

void AccountState::updateSFMLEvents()
{
		while (this->window->pollEvent(this->event)) {
			if (this->event.type == sf::Event::TextEntered) 
				if (write_on_emailText) {
					if (std::isprint(this->event.text.unicode))
						this->emailInput += this->event.text.unicode;
				}
				else {
					if (std::isprint(this->event.text.unicode)) {
						this->passwordInput += this->event.text.unicode;
						this->passwordAsterisk += '*';
					}
				}

			if (this->event.type == sf::Event::KeyPressed) {
				if (this->event.key.code == sf::Keyboard::BackSpace)
					if (write_on_emailText) {
						if (!emailInput.empty())
							this->emailInput.pop_back();
					}
					else {
						if (!passwordInput.empty()) {
							this->passwordInput.pop_back();
							this->passwordAsterisk.pop_back();
						}
					}

				if (this->event.key.code == sf::Keyboard::Tab)
					this->write_on_emailText = !this->write_on_emailText;
			}
				

			if (this->event.type == sf::Event::Closed)
				this->window->close();
		}
}

bool AccountState::verifAccount(std::string email, std::string password)
{
	if (this->accountDataBase->isConnected()) {
		MYSQL_RES* result;
		MYSQL_ROW row = NULL;
		int query_rez;
		bool ok = false;

		std::string query = "SELECT `Email`,`Password` FROM `users` WHERE `Email` = '" + email + "' AND `Password` = '" + password + "'"; //the query

		query_rez = mysql_query(this->accountDataBase->getConnection(), query.c_str()); //send the query

		result = mysql_store_result(this->accountDataBase->getConnection()); //store the result

		if (result)
			row = mysql_fetch_row(result);
		mysql_free_result(result);

		if (row)
			ok = true;

		return ok;
	}
	return false;
}

void AccountState::updateCursor() {
	this->text_effect_time += this->clock.restart();
	if (this->text_effect_time >= sf::seconds(0.5f)) {
		this->show_cursor = !this->show_cursor;
		this->text_effect_time = sf::Time::Zero;
	}
	if (write_on_emailText) {
		this->emailText.setString(emailInput + (show_cursor ? '|' : ' '));
		this->passwordText.setString(passwordAsterisk);
	}
	else {
		this->emailText.setString(emailInput);
		this->passwordText.setString(passwordAsterisk + (show_cursor ? '|' : ' '));
	}
}

void AccountState::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);
	
	//Connection to the database -> Next state
	if (this->buttons["CONNECT"]->isPressed()) {
		if (this->verifAccount(emailInput, passwordInput)) {
			std::cout << "\nAccount connected!";
			this->wrongAccount.setString("");
			this->numberOfFailedEntries = 0;
			//Next state
			this->states->push(new SearchState(this->window, this->states, this->accountDataBase));
		}
		else {
			std::cout << "\nWrong email or password!";
			this->accountConnected = false;
			this->wrongAccount.setString(wrongAccountString + std::to_string(numberOfFailedEntries));
			numberOfFailedEntries++;
		}
	}
	
	//Register an account
	if (this->buttons["REGISTER"]->isPressed()) {
		//Register state
		this->states->push(new RegistrationState(this->window, this->states, this->accountDataBase));
	}

	//Quit the app
	if (this->buttons["EXIT"]->isPressed()) {
		accountDataBase->closeConnection(accountDataBase->getConn());
		this->endState();
	}
		
	//Select the email box
	if (this->buttons["EMAIL"]->isPressed()) 
		this->write_on_emailText = true;
	
	//Select the password box
	if (this->buttons["PASSWORD"]->isPressed()) 
		this->write_on_emailText = false;
}

void AccountState::update()
{
	this->updateSFMLEvents();
	this->updateCursor();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void AccountState::renderText(sf::RenderTarget* target)
{
	target->draw(this->title);
	target->draw(this->emailLabel);
	target->draw(this->passwordLabel);
}

void AccountState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
}

void AccountState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);
	this->renderText(target);
	target->draw(this->emailText);
	target->draw(this->passwordText);
	if (!this->accountConnected)
		target->draw(this->wrongAccount);
	this->window->display();
}