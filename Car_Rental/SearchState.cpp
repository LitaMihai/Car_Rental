#include "SearchState.h"

void SearchState::initWindow(sf::RenderWindow* window)
{
	this->prevWindow = window;
	this->prevWindow->setActive(false);
	this->prevWindow->setVisible(false);

	std::string title = "Car Rental";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	window_bounds.width = 1600;
	window_bounds.height = 900;
	windowSettings.antialiasingLevel = 0;

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(60);

	if (!this->icon.loadFromFile("Resources/Images/Icon/icon.png"))
		throw "ERROR::SEARCHSTATE::FAILED_TO_LOAD_ICON_IMAGE";
	this->window->setIcon(this->icon.getSize().x, this->icon.getSize().y, this->icon.getPixelsPtr());
}

void SearchState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Background/bg.png"))
		throw "ERROR::SEARCHSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	this->background.setTexture(&this->backgroundTexture);
}

void SearchState::initLines()
{
	/*this->linie[0].setFillColor(sf::Color::White);
	this->linie[0].setSize(sf::Vector2f(1600.f, 1.f));
	this->linie[0].setPosition(0.f, 40.f);

	this->linie[1].setFillColor(sf::Color::White);
	this->linie[1].setSize(sf::Vector2f(1.f, 900.f));
	this->linie[1].setPosition(225.f, 40.f);

	this->linie[2].setFillColor(sf::Color::White);
	this->linie[2].setSize(sf::Vector2f(1.f, 900.f));
	this->linie[2].setPosition(450.f, 40.f);

	this->linie[3].setFillColor(sf::Color::White);
	this->linie[3].setSize(sf::Vector2f(800.f, 1.f));
	this->linie[3].setPosition(800.f, 600.f);*/
}

void SearchState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::SEARCHSTATE::COULD NOT LOAD FONT");
}

void SearchState::initText()
{
}

void SearchState::initButtons()
{
	this->buttons["LOG_OUT"] = new Button(
		1515.f, 5.f, 70.f, 30.f,
		&this->font,
		"Log Out", 25,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void SearchState::initMake()
{
	
}

void SearchState::initModel()
{
}

SearchState::SearchState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* accountDataBase) : State(window, states)
{
	this->initWindow(window);
	this->initBackground();
	this->initLines();
	this->initFonts();
	this->initText();
	this->initButtons();
}

SearchState::~SearchState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;

	auto it1 = this->make.begin();
	for (it1 = this->make.begin(); it1 != this->make.end(); ++it1)
		delete it1->second;

	auto it2 = this->model.begin();
	for (it2 = this->model.begin(); it2 != this->model.end(); ++it2)
		delete it2->second;
}

void SearchState::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::KeyPressed) {
			if (this->event.key.code == sf::Keyboard::Escape)
				this->endState();
		}

		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

void SearchState::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);

	if (this->buttons["LOG_OUT"]->isPressed()) {
		this->endState();
		this->window->close();
		this->prevWindow->setActive(true);
		this->prevWindow->setVisible(true);
	}
}

void SearchState::update()
{
	this->updateSFMLEvents();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void SearchState::renderText(sf::RenderTarget* target)
{

}

void SearchState::renderLines(sf::RenderTarget* target)
{
	/*for (int i = 0; i < 4; i++)
		target->draw(this->linie[i]);*/
}

void SearchState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
		it.second->render(target);
}

void SearchState::render(sf::RenderTarget* target)
{
	target = this->window;
	target->draw(this->background);
	
	this->renderButtons(target);
	this->renderLines(target);
	this->renderText(target);
	this->window->display();
}
