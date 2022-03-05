#include "ForgotPassCodeState.h"

void ForgotPassCodeState::initVariables()
{
	this->codeInput = "";
	this->codeText.setString("");
	this->codeLabel.setString("");

	this->incorrectCode.setString("");

	this->email.setString("");
	this->anEmailWasSent.setString("An email with a code was sent to:");
	this->pleaseEnterTheCodeBelow.setString("Please enter the code below");
	this->ifIsRegistrated.setString("if an account is registered with this address!");
}

void ForgotPassCodeState::initBackground()
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

void ForgotPassCodeState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
}

void ForgotPassCodeState::initText()
{
	this->codeLabel.setFont(this->font);
	this->codeLabel.setFillColor(sf::Color::White);
	this->codeLabel.setCharacterSize(40);
	this->codeLabel.setPosition(sf::Vector2f(80, 315));
	this->codeLabel.setString("Code");

	this->incorrectCode.setFont(this->font);
	this->incorrectCode.setFillColor(sf::Color::Red);
	this->incorrectCode.setCharacterSize(32);
	this->incorrectCode.setPosition(sf::Vector2f(250, 450));

	this->codeText.setFont(this->font);
	this->codeText.setFillColor(sf::Color::Black);
	this->codeText.setCharacterSize(28);
	this->codeText.setPosition(sf::Vector2f(255, 323));

	this->email.setFont(this->font);
	this->email.setFillColor(sf::Color::White);
	this->email.setCharacterSize(40);
	this->email.setPosition(sf::Vector2f(240, 90));
	this->email.setString(this->emailString);

	this->anEmailWasSent.setFillColor(sf::Color::White);
	this->anEmailWasSent.setCharacterSize(40);
	this->anEmailWasSent.setPosition(sf::Vector2f(150, 40));
	this->anEmailWasSent.setFont(this->font);

	this->pleaseEnterTheCodeBelow.setFillColor(sf::Color::White);
	this->pleaseEnterTheCodeBelow.setCharacterSize(30);
	this->pleaseEnterTheCodeBelow.setPosition(sf::Vector2f(320, 280));
	this->pleaseEnterTheCodeBelow.setFont(this->font);

	this->ifIsRegistrated.setFillColor(sf::Color::White);
	this->ifIsRegistrated.setCharacterSize(40);
	this->ifIsRegistrated.setPosition(sf::Vector2f(100, 140));
	this->ifIsRegistrated.setFont(this->font);
}

void ForgotPassCodeState::initButtons()
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

bool ForgotPassCodeState::codeVerif(std::string codeInput)
{
	if (*this->code == atoi(codeInput.c_str()))
		return true;

	return false;
}

ForgotPassCodeState::ForgotPassCodeState(sf::RenderWindow* window, std::stack<State*>* states, std::string* emailString, int* code) : State(window, states), code(code), emailString(*emailString)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initButtons();
}

ForgotPassCodeState::~ForgotPassCodeState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;
}

void ForgotPassCodeState::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->endState();
			this->window->close();
		}

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

void ForgotPassCodeState::updateCursor()
{
	this->text_effect_time += this->clock.restart();
	if (this->text_effect_time >= sf::seconds(0.5f)) {
		this->show_cursor = !this->show_cursor;
		this->text_effect_time = sf::Time::Zero;
	}

	this->codeText.setString(this->codeInput + (show_cursor ? '|' : ' '));
}

void ForgotPassCodeState::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);

	if (this->buttons["CONFIRM"]->isPressed()) {
		if (codeVerif(this->codeInput)) {
			this->states->push(new ForgotPass_NewPass_State(this->window, this->states, &this->emailString));
		}
		else {
			this->incorrectCode.setString("The code is not correct!!!");
		}
	}

	if (this->buttons["CANCEL"]->isPressed()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->states->top()->endState();
	}
}

void ForgotPassCodeState::update()
{
	this->updateSFMLEvents();
	this->updateCursor();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void ForgotPassCodeState::renderText(sf::RenderTarget* target)
{
	target->draw(this->codeLabel);

	target->draw(this->email);
	target->draw(this->anEmailWasSent);
	target->draw(this->pleaseEnterTheCodeBelow);
	target->draw(this->ifIsRegistrated);

	target->draw(this->codeText);
	target->draw(this->incorrectCode);
}

void ForgotPassCodeState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
}

void ForgotPassCodeState::render(sf::RenderTarget* target)
{
	target->draw(this->background);

	this->renderButtons(target);
	this->renderText(target);

	this->window->display();
}
