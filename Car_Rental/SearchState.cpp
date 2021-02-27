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

void SearchState::initView()
{/*
	this->makeView.setCenter(sf::Vector2f(0.f, 0.f));
	this->makeView.setSize(sf::Vector2f(258.f, 608.f));
	this->makeView.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));
	this->window->setView(makeView);
	*/
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
	this->linie[0].setFillColor(sf::Color::White);
	this->linie[0].setSize(sf::Vector2f(1600.f, 1.f));
	this->linie[0].setPosition(0.f, 40.f);

	this->linie[1].setFillColor(sf::Color::White);
	this->linie[1].setSize(sf::Vector2f(1.f, 900.f));
	this->linie[1].setPosition(225.f, 40.f);

	this->linie[2].setFillColor(sf::Color::Black);//Invisible at start
	this->linie[2].setSize(sf::Vector2f(1.f, 900.f));
	this->linie[2].setPosition(450.f, 41.f);

	this->linie[3].setFillColor(sf::Color::Black);//Invisible at start
	this->linie[3].setSize(sf::Vector2f(800.f, 1.f));
	this->linie[3].setPosition(800.f, 601.f);
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
	this->buttons["ALFA_ROMEO"] = new Button(
		0.f, 40.f, 225.f, 25.f,
		&this->font,
		"Alfa Romeo", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["ASTON_MARTIN"] = new Button(
		0.f, 65.f, 225.f, 25.f,
		&this->font,
		"Aston Martin", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["AUDI"] = new Button(
		0.f, 90.f, 225.f, 25.f,
		&this->font,
		"Audi", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["BENTLEY"] = new Button(
		0.f, 115.f, 225.f, 25.f,
		&this->font,
		"Bentley", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["BMW"] = new Button(
		0.f, 140.f, 225.f, 25.f,
		&this->font,
		"BMW", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["BUGATTI"] = new Button(
		0.f, 165.f, 225.f, 25.f,
		&this->font,
		"Bugatti", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["CADILLAC"] = new Button(
		0.f, 190.f, 225.f, 25.f,
		&this->font,
		"Cadillac", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["CHEVROLET"] = new Button(
		0.f, 215.f, 225.f, 25.f,
		&this->font,
		"Chevrolet", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
	
	this->buttons["CITROEN"] = new Button(
		0.f, 240.f, 225.f, 25.f,
		&this->font,
		"Citroën", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["DACIA"] = new Button(
		0.f, 265.f, 225.f, 25.f,
		&this->font,
		"Dacia", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["DAEWOO"] = new Button(
		0.f, 290.f, 225.f, 25.f,
		&this->font,
		"Daewoo", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["DODGE"] = new Button(
		0.f, 315.f, 225.f, 25.f,
		&this->font,
		"Dodge", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["FERRARI"] = new Button(
		0.f, 340.f, 225.f, 25.f,
		&this->font,
		"Ferrari", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["FIAT"] = new Button(
		0.f, 365.f, 225.f, 25.f,
		&this->font,
		"Fiat", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["FORD"] = new Button(
		0.f, 390.f, 225.f, 25.f,
		&this->font,
		"Ford", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["HONDA"] = new Button(
		0.f, 415.f, 225.f, 25.f,
		&this->font,
		"Honda", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["HYUNDAI"] = new Button(
		0.f, 440.f, 225.f, 25.f,
		&this->font,
		"Hyundai", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["JAGUAR"] = new Button(
		0.f, 465.f, 225.f, 25.f,
		&this->font,
		"Jaguar", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["JEEP"] = new Button(
		0.f, 490.f, 225.f, 25.f,
		&this->font,
		"Jeep", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["LAMBORGHINI"] = new Button(
		0.f, 515.f, 225.f, 25.f,
		&this->font,
		"Lamborghini", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["LAND_ROVER"] = new Button(
		0.f, 540.f, 225.f, 25.f,
		&this->font,
		"Land Rover", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["MASERATI"] = new Button(
		0.f, 565.f, 225.f, 25.f,
		&this->font,
		"Maserati", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["MAYBACH"] = new Button(
		0.f, 590.f, 225.f, 25.f,
		&this->font,
		"Maybach", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["MAZDA"] = new Button(
		0.f, 615.f, 225.f, 25.f,
		&this->font,
		"Mazda", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["MERCEDES_BENZ"] = new Button(
		0.f, 640.f, 225.f, 25.f,
		&this->font,
		"Mercedes-Benz", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["MITSUBISHI"] = new Button(
		0.f, 665.f, 225.f, 25.f,
		&this->font,
		"Mitsubishi", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["NISSAN"] = new Button(
		0.f, 690.f, 225.f, 25.f,
		&this->font,
		"Nissan", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["OPEL"] = new Button(
		0.f, 715.f, 225.f, 25.f,
		&this->font,
		"Opel", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["PEUGEOT"] = new Button(
		0.f, 740.f, 225.f, 25.f,
		&this->font,
		"Peugeot", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["PORCHE"] = new Button(
		0.f, 765.f, 225.f, 25.f,
		&this->font,
		"Porche", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["RENAULT"] = new Button(
		0.f, 790.f, 225.f, 25.f,
		&this->font,
		"Renault", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["ROLLS_ROYCE"] = new Button(
		0.f, 815.f, 225.f, 25.f,
		&this->font,
		"Rolls-Royce", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["SEAT"] = new Button(
		0.f, 840.f, 225.f, 25.f,
		&this->font,
		"Seat", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["SKODA"] = new Button(
		0.f, 865.f, 225.f, 25.f,
		&this->font,
		"Skoda", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["SUBARU"] = new Button(
		0.f, 890.f, 225.f, 25.f,
		&this->font,
		"Subaru", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["SUZUKI"] = new Button(
		0.f, 740.f, 225.f, 25.f,
		&this->font,
		"Suzuki", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["TESLA"] = new Button(
		0.f, 740.f, 225.f, 25.f,
		&this->font,
		"Tesla", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["TOYOTA"] = new Button(
		0.f, 740.f, 225.f, 25.f,
		&this->font,
		"Toyota", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["VOLKSWAGEN"] = new Button(
		0.f, 740.f, 225.f, 25.f,
		&this->font,
		"Volkswagen", 20,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void SearchState::initModel()
{

}

SearchState::SearchState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* accountDataBase) : State(window, states)
{
	this->initWindow(window);
	this->initView();
	this->initBackground();
	this->initLines();
	this->initFonts();
	this->initText();
	this->initButtons();
	this->initMake();
	this->initModel();
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

	std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";
}

void SearchState::renderText(sf::RenderTarget* target)
{

}

void SearchState::renderLines(sf::RenderTarget* target)
{
	for (int i = 0; i < 4; i++)
		target->draw(this->linie[i]);
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
