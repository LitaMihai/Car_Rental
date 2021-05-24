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

void SearchState::initVariables()
{
	this->renderLineForModels = false;
	this->renderTheLastLine = false;
	this->seePhoto = false;
	this->buttonsMoved = false;
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
	this->linie[3].setSize(sf::Vector2f(1150.f, 1.f));
	this->linie[3].setPosition(450.f, 701.f);
}

void SearchState::initFonts()
{
	if (!this->font.loadFromFile("Resources/Font/Dosis-Light.ttf"))
		throw("ERROR::SEARCHSTATE::COULD NOT LOAD FONT");
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

	this->buttons["RENT"] = new Button(
		1215.f, 730.f, 150.f, 100.f,
		&this->font,
		"Rent", 50,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["DETAILS"] = new Button(
		700.f, 730.f, 150.f, 100.f,
		&this->font,
		"Details", 50,
		sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["LEFT"] = new Button(
		0.f, -100.f, 45.f, 30.f,
		&this->font,
		"RIGHT", 25,
		sf::Color(250, 250, 250, 0), sf::Color(250, 250, 250, 0), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 100), sf::Color(20, 20, 20, 105)
	);

	this->buttons["RIGHT"] = new Button(
		0.f, -100.f, 45.f, 30.f,
		&this->font,
		"LEFT", 25,
		sf::Color(250, 250, 250, 0), sf::Color(250, 250, 250, 0), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 100), sf::Color(20, 20, 20, 105)
	);

	this->leftButtonTexture.loadFromFile("Resources/Images/Left_Right_Buttons/Left.png");
	this->leftButtonTexture.setSmooth(true);
	this->leftButtonSprite.setTexture(leftButtonTexture);
	this->leftButtonSprite.setPosition(sf::Vector2f(0.f, -100.f));
	this->leftButtonSprite.setScale(static_cast<float>(0.2), static_cast<float>(0.2));

	this->rightButtonTexture.loadFromFile("Resources/Images/Left_Right_Buttons/Right.png");
	this->rightButtonTexture.setSmooth(true);
	this->rightButtonSprite.setTexture(rightButtonTexture);
	this->rightButtonSprite.setPosition(sf::Vector2f(0.f, -100.f));
	this->rightButtonSprite.setScale(static_cast<float>(0.2), static_cast<float>(0.2));
}

void SearchState::initMake()
{
	std::ifstream i("Resources/Makes/Makes.json");
	json j;
	i >> j;
	i.close();

	float y = 40.f;
	for (auto& x : j.items()) {

		std::string name = x.value().find("Make").value();

		this->make[name] = new Button(
			0.f, y, 225.f, 25.f,
			&this->font,
			name, 20,
			sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);

		y += 25.f;
	}
}

void SearchState::initModel()
{
	std::ifstream i("Resources/Makes/Cars.json");
	json j;
	i >> j;
	i.close();

	for (auto& x : j.items()) {

		std::string name = x.value().find("Model").value();

		this->model[name] = new Button(
			0.f, -100.f, 225.f, 25.f,
			&this->font,
			name, 20,
			sf::Color(250, 250, 250, 250), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
		);
	}
}

SearchState::SearchState(sf::RenderWindow* window, std::stack<State*>* states, DbConnection* accountDataBase) : State(window, states)
{
	this->initWindow(window);
	this->initVariables();
	this->initBackground();
	this->initLines();
	this->initFonts();
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

	for (auto& it1: this->make)
		it1.second->update(this->mousePosView);

	for (auto& it1 : this->model)
		it1.second->update(this->mousePosView);

	if (this->buttons["LOG_OUT"]->isPressed()) {
		this->endState();
		this->window->close();
		this->prevWindow->setActive(true);
		this->prevWindow->setVisible(true);
	}

	for (auto& it1 : this->make)
		if (it1.second->isPressed()) {
			this->renderLineForModels = true;

			for (auto& it2 : this->model)
				it2.second->move(0.f, -100.f);

			std::string name = it1.second->returnName(); // the make to search in the cars json

			std::ifstream i("Resources/Makes/Cars.json");
			json j;
			i >> j;
			i.close();

			int nr = 0;
			float x_init = 225.f, y_init = 400.f;
			for (auto& x : j.items()) { 

				if (x.value().find("Make").value() == name) {
					nr++;

					for(auto& it2 : this->model)
						if (it2.second->returnName() == x.value().find("Model").value()) {
							it2.second->move(x_init, y_init);
							y_init += 50.f;
						}
				}

				if (nr == 3)// we know that there are only 3 cars for each make so we don't need to search further
					break;
			}
		}

	for (auto& it1 : this->model)
		if (it1.second->isPressed()) {
			this->renderTheLastLine = true;
			this->seePhoto = true;

			if (!this->buttonsMoved) {
				for (auto& it2 : this->buttons) {

					if (it2.second->returnName() == "LEFT") {
						it2.second->move(460.f, 320.f);
						this->leftButtonSprite.setPosition(460.f, 320.f);
					}

					if (it2.second->returnName() == "RIGHT") {
						it2.second->move(1550.f, 320.f);
						this->rightButtonSprite.setPosition(1550.f, 320.f);
					}
				}
				this->buttonsMoved = true;
			}

			std::string way1 = "Resources/Makes/", way2 = "Resources/Makes/";

			std::string makeFolderName;
			std::string modelFolderName = it1.second->returnName();

			std::ifstream i("Resources/Makes/Cars.json");
			json j;
			i >> j;
			i.close();

			for (auto& x : j.items()) 
				if (x.value().find("Model").value() == modelFolderName) {
					makeFolderName = x.value().find("Make").value();
					break;
				}

			way1 = way1 + makeFolderName + "/" + modelFolderName + "/" + modelFolderName + "_1.jpg";
			way2 = way2 + makeFolderName + "/" + modelFolderName + "/" + modelFolderName + "_2.jpg";
			
			this->firstPhotoTexture.loadFromFile(way1);
			this->firstPhotoTexture.setSmooth(true);

			this->secondPhotoTexture.loadFromFile(way2);
			this->secondPhotoTexture.setSmooth(true);

			this->shape.setTexture(&this->firstPhotoTexture);
			this->shape.setPosition(sf::Vector2f(503.f, 40.f));
			this->shape.setSize(sf::Vector2f(1044.f, 661.f));
		}

	for (auto& it1 : this->buttons) {
		if (it1.second->returnName() == "LEFT") {
			if (it1.second->isPressed()) {
				this->shape.setTexture(&this->firstPhotoTexture);
			}
		}

		if (it1.second->returnName() == "RIGHT") {
			if (it1.second->isPressed()) {
				this->shape.setTexture(&this->secondPhotoTexture);
			}
		}
	}
}

void SearchState::update()
{
	this->updateSFMLEvents();
	this->updateMousePositions(this->window);
	this->updateButtons();

	std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n"; /*TO BE DELETED!!!*/
}

void SearchState::renderLines(sf::RenderTarget* target)
{
	if (this->renderLineForModels)
		linie[2].setFillColor(sf::Color::White);

	if (this->renderTheLastLine)
		linie[3].setFillColor(sf::Color::White);

	for (int i = 0; i < 4; i++)
		target->draw(this->linie[i]);
}

void SearchState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
		it.second->render(target);

	for (auto& it1 : this->make)
		it1.second->render(target);

	for (auto& it1 : this->model)
		it1.second->render(target);
}

void SearchState::render(sf::RenderTarget* target)
{
	target = this->window;
	target->draw(this->background);
	target->draw(this->leftButtonSprite);
	target->draw(this->rightButtonSprite);

	if (seePhoto) 
		target->draw(this->shape);

	this->renderLines(target);
	this->renderButtons(target);
	this->window->display();
	
}