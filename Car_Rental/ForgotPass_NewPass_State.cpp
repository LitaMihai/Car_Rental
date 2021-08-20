#include "ForgotPass_NewPass_State.h"

void ForgotPass_NewPass_State::initVariables()
{
	this->passInput = "";
	this->passConfirmationInput = "";

	this->passAsterisk = "";
	this->passConfirmationAsterisk = "";

	this->passText.setString("");
	this->passConfirmationText.setString("");

	this->failedConfirmation.setString("");

	this->showPassword = false;
	this->show_cursor = true;

	this->title.setString("Please enter a new password!");
	this->passLabel.setString("Password");
	this->passConfirmationLabel.setString("Confirm Password");

	this->writeOnPasswordText = true;
	this->writeOnConfirmPasswordText = false;
}

void ForgotPass_NewPass_State::initBackground()
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

void ForgotPass_NewPass_State::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void ForgotPass_NewPass_State::initText()
{
	this->title.setFont(this->font);
	this->title.setFillColor(sf::Color::White);
	this->title.setCharacterSize(48);
	this->title.setPosition(sf::Vector2f(150, 100));

	this->passText.setFont(this->font);
	this->passText.setFillColor(sf::Color::Black);
	this->passText.setCharacterSize(28);
	this->passText.setPosition(sf::Vector2f(255, 273));

	this->passConfirmationText.setFont(this->font);
	this->passConfirmationText.setFillColor(sf::Color::Black);
	this->passConfirmationText.setCharacterSize(28);
	this->passConfirmationText.setPosition(sf::Vector2f(255, 343));

	this->passLabel.setFont(this->font);
	this->passLabel.setFillColor(sf::Color::White);
	this->passLabel.setCharacterSize(32);
	this->passLabel.setPosition(sf::Vector2f(20, 270));

	this->passConfirmationLabel.setFont(this->font);
	this->passConfirmationLabel.setFillColor(sf::Color::White);
	this->passConfirmationLabel.setCharacterSize(32);
	this->passConfirmationLabel.setPosition(sf::Vector2f(20, 340));

	this->failedConfirmation.setFont(this->font);
	this->failedConfirmation.setFillColor(sf::Color::Red);
	this->failedConfirmation.setCharacterSize(32);
	this->failedConfirmation.setPosition(sf::Vector2f(260, 450));
}

void ForgotPass_NewPass_State::initButtons()
{
	this->buttons["CONFIRM"] = new Button(
		50.f, 490.f, 175.f, 70.f,
		&this->font,
		"Confirm", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["CANCEL"] = new Button(
		620.f, 490.f, 100.f, 70.f,
		&this->font,
		"Cancel", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["PASSWORD"] = new Button(
		250.f, 275.f, 500.f, 35.f,
		&this->font,
		"", 50,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

	this->buttons["CONFIRMPASSWORD"] = new Button(
		250.f, 345.f, 500.f, 35.f,
		&this->font,
		"", 50,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);

	this->buttons["SHOWPASSWORD"] = new Button(
		753.f, 310.f, 45.f, 40.f,
		&this->font,
		"", 50,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 250)
	);

	// Init the hide password button
	this->showButtonTexture.loadFromFile("Resources/Images/Show_Hide_Buttons/Hide button.png");
	this->showButtonTexture.setSmooth(true);
	this->showButtonSprite.setTexture(showButtonTexture);
	this->showButtonSprite.setPosition(sf::Vector2f(760.f, 320.f));
	this->showButtonSprite.setScale(0.3f, 0.3f);
}

bool ForgotPass_NewPass_State::verifPasswords(std::string pass1, std::string pass2)
{
	if (pass1.compare(pass2) == 0)
		return true;
	else
		return false;
}

bool ForgotPass_NewPass_State::changePassword(std::string pass)
{
	if (this->accountDataBase->isConnected()) {
		MYSQL_RES* result;
		MYSQL_ROW row = NULL;
		int query_rez;
		bool ok = false;

		Hash_t hashedPassword(pass);
		pass = hashedPassword.ReturnHash();

		std::string query = "UPDATE `users` SET `Password`='" + pass + "' WHERE `Email` = '" + *this->email + "'"; //the query

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
}

ForgotPass_NewPass_State::ForgotPass_NewPass_State(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* accountDataBase, std::string* email) : State(window, states), accountDataBase(accountDataBase), email(email)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initButtons();
}

ForgotPass_NewPass_State::~ForgotPass_NewPass_State()
{
}

void ForgotPass_NewPass_State::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed)
			this->window->close();

		if (this->event.type == sf::Event::TextEntered) {
			if (writeOnPasswordText) {
				if (std::isprint(this->event.text.unicode)) {
					this->passInput += this->event.text.unicode;
					this->passAsterisk += '*';
				}
			}
			else if (writeOnConfirmPasswordText) {
				if (std::isprint(this->event.text.unicode)) {
					this->passConfirmationInput += this->event.text.unicode;
					this->passConfirmationAsterisk += '*';
				}
			}
		}

		if (this->event.type == sf::Event::KeyPressed) {
			if (this->event.key.code == sf::Keyboard::BackSpace) {
				if (writeOnPasswordText) {
					if (!passInput.empty()) {
						this->passInput.pop_back();
						this->passAsterisk.pop_back();
					}
				}

				else if (writeOnConfirmPasswordText) {
					if (!passConfirmationInput.empty()) {
						this->passConfirmationInput.pop_back();
						this->passConfirmationAsterisk.pop_back();
					}
				}
			}

			if (this->event.key.code == sf::Keyboard::Tab) {
				if (writeOnPasswordText) {
					this->writeOnPasswordText = false;
					this->writeOnConfirmPasswordText = true;
				}
				else if (writeOnConfirmPasswordText) {
					this->writeOnPasswordText = true;
					this->writeOnConfirmPasswordText = false;
				}
			}
		}
	}
}

void ForgotPass_NewPass_State::updateCursor()
{
	this->text_effect_time += this->clock.restart();
	if (this->text_effect_time >= sf::seconds(0.5f)) {
		this->show_cursor = !this->show_cursor;
		this->text_effect_time = sf::Time::Zero;
	}

	else if (writeOnPasswordText) {
		if (this->showPassword) {
			this->passText.setString(this->passInput + (show_cursor ? '|' : ' '));
			this->passConfirmationText.setString(this->passConfirmationInput);
		}
		else {
			this->passText.setString(this->passAsterisk + (show_cursor ? '|' : ' '));
			this->passConfirmationText.setString(this->passConfirmationAsterisk);
		}
	}

	else if (writeOnConfirmPasswordText) {
		if (this->showPassword) {
			this->passText.setString(this->passInput);
			this->passConfirmationText.setString(this->passConfirmationInput + (show_cursor ? '|' : ' '));
		}
		else {
			this->passText.setString(this->passAsterisk);
			this->passConfirmationText.setString(this->passConfirmationAsterisk + (show_cursor ? '|' : ' '));
		}

	}
}

void ForgotPass_NewPass_State::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);

	if (this->buttons["CONFIRM"]->isPressed()) {
		if (this->verifPasswords(this->passInput, this->passConfirmationInput)) {
			this->changePassword(this->passInput);
			this->states->pop();
			this->states->pop();
			this->states->pop();
		}
		else {
			this->failedConfirmation.setString("Passwords mismatch!");
		}
	}

	if (this->buttons["PASSWORD"]->isPressed()) {
		this->writeOnPasswordText = true;
		this->writeOnConfirmPasswordText = false;
	}

	if (this->buttons["CONFIRMPASSWORD"]->isPressed()) {
		this->writeOnPasswordText = false;
		this->writeOnConfirmPasswordText = true;
	}

	if (this->buttons["CANCEL"]->isPressed()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->states->top()->endState();
	}

	if (this->buttons["SHOWPASSWORD"]->isPressed()) {
		this->showPassword = !this->showPassword;

		if (this->showPassword == false) {
			this->showButtonTexture.loadFromFile("Resources/Images/Show_Hide_Buttons/Hide button.png");
			this->showButtonTexture.setSmooth(true);
		}

		else {
			this->showButtonTexture.loadFromFile("Resources/Images/Show_Hide_Buttons/Show button.png");
			this->showButtonTexture.setSmooth(true);
		}

		this->showButtonSprite.setTexture(this->showButtonTexture);
	}
}

void ForgotPass_NewPass_State::update()
{
	this->updateSFMLEvents();
	this->updateCursor();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void ForgotPass_NewPass_State::renderText(sf::RenderTarget* target)
{
	target->draw(passText);
	target->draw(passConfirmationText);

	target->draw(failedConfirmation);

	target->draw(title);
	target->draw(passLabel);
	target->draw(passConfirmationLabel);
}

void ForgotPass_NewPass_State::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
		it.second->render(target);

	target->draw(this->showButtonSprite);
}

void ForgotPass_NewPass_State::render(sf::RenderTarget* target)
{
	target->draw(this->background);

	this->renderButtons(target);
	this->renderText(target);

	this->window->display();
}
