#include "EmailVerificationState.h"

void EmailVerificationState::initVariables()
{
	this->codeInput = "";
	this->codeText.setString("");
	this->codeLabel.setString("");

	this->incorrectCode.setString("");
}

void EmailVerificationState::initBackground()
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

void EmailVerificationState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void EmailVerificationState::initText()
{
	this->codeLabel.setFont(this->font);
	this->codeLabel.setFillColor(sf::Color::White);
	this->codeLabel.setCharacterSize(32);
	this->codeLabel.setPosition(sf::Vector2f(20, 320));
	this->codeLabel.setString("Code");

	this->incorrectCode.setFont(this->font);
	this->incorrectCode.setFillColor(sf::Color::White);
	this->incorrectCode.setCharacterSize(32);
	this->incorrectCode.setPosition(sf::Vector2f(20, 450));

	this->codeText.setFont(this->font);
	this->codeText.setFillColor(sf::Color::Black);
	this->codeText.setCharacterSize(28);
	this->codeText.setPosition(sf::Vector2f(255, 323));
}

void EmailVerificationState::initButtons()
{
	this->buttons["CANCEL"] = new Button(
		620.f, 490.f, 100.f, 70.f,
		&this->font,
		"Cancel", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["CONFIRM"] = new Button(
		50.f, 490.f, 175.f, 70.f,
		&this->font,
		"Confirm", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["CODE"] = new Button(
		250.f, 325.f, 500.f, 35.f,
		&this->font,
		"", 50,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255)
	);
}

bool EmailVerificationState::codeVerif(std::string codeInput)
{
	if(*this->code == atoi(codeInput.c_str()))
		return true;
	
	return false;
}

EmailVerificationState::EmailVerificationState(sf::RenderWindow* window, std::stack<State*>* states, int* code, bool *continueRegistration) : State(window, states), code(code), continueRegistration(continueRegistration)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initButtons();
}

EmailVerificationState::~EmailVerificationState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;
}

void EmailVerificationState::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed)
			this->window->close();

		if (this->event.type == sf::Event::TextEntered)
			if (std::isprint(this->event.text.unicode))
				this->codeInput += this->event.text.unicode;

		if (this->event.type == sf::Event::KeyPressed) {
			if (this->event.key.code == sf::Keyboard::BackSpace)
				if (!codeInput.empty())
					this->codeInput.pop_back();
		}
	}
}

void EmailVerificationState::updateCursor()
{
	this->text_effect_time += this->clock.restart();
	if (this->text_effect_time >= sf::seconds(0.5f)) {
		this->show_cursor = !this->show_cursor;
		this->text_effect_time = sf::Time::Zero;
	}

	this->codeText.setString(this->codeInput + (show_cursor ? '|' : ' '));
}

void EmailVerificationState::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);

	if (this->buttons["CONFIRM"]->isPressed()) {
		if (codeVerif(this->codeInput)) {
			*this->continueRegistration = true;

			this->states->top()->endState();
		}
		else {
			this->incorrectCode.setString("The code is not correct!!!");
		}
	}

	if (this->buttons["CANCEL"]->isPressed()) {
		*this->continueRegistration = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->states->top()->endState();
	}
}

void EmailVerificationState::update()
{
	this->updateSFMLEvents();
	this->updateCursor();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void EmailVerificationState::renderText(sf::RenderTarget* target)
{
	target->draw(this->codeLabel);
}

void EmailVerificationState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
}

void EmailVerificationState::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	this->renderButtons(target);
	this->renderText(target);

	target->draw(this->codeText);
	target->draw(this->incorrectCode);

	this->window->display();
}
