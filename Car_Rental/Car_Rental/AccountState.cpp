#include "AccountState.h"

void AccountState::initVariables()
{
	this->Email = "";
	this->Password = "";
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
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void AccountState::initButtons()
{
	this->buttons["CONFIRM"] = new Button(
		350.f, 190.f, 250.f, 50.f,
		&this->font,
		"Confirm", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["Exit"] = new Button(
		450.f, 190.f, 250.f, 50.f,
		&this->font,
		"Exit", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

AccountState::AccountState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
}

AccountState::~AccountState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) 
		delete it->second;
}

void AccountState::updateInput(const float& dt)
{
}

void AccountState::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);
	
	//Confirm
	if (this->buttons["CONFIRM"]->isPressed());
		//Next state
	
	//Quit the app
	if (this->buttons["EXIT"]->isPressed())
		this->endState();
}

void AccountState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
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
}
