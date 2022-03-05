#include "AccountSettings.h"

void AccountSettings::initText(){
    this->accountSettings.setFillColor(sf::Color::White);
	this->accountSettings.setCharacterSize(40);
	this->accountSettings.setPosition(sf::Vector2f(280, 60));
	this->accountSettings.setFont(font);
	this->accountSettings.setString("Account Settings");
}

void AccountSettings::initButtons(){
    this->buttons["CHANGE_EMAIL"] = new Button(
		25.f, 200.f,
		225.f, 50.f,
		&font,
		"Change Email", 30,
		sf::Color(238, 238, 238, 255), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(0, 173, 181, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["CHANGE_PASSWORD"] = new Button(
		50.f, 400.f, 
		225.f, 50.f,
		&font,
		"Change Password", 30,
		sf::Color(238, 238, 238, 255), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(0, 173, 181, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
	
	this->buttons["CLOSE"] = new Button(
		625, 500,
		100.f, 70.f,
		&font,
		"Close", 30,
		sf::Color(238, 238, 238, 255), sf::Color(250, 250, 250, 75), sf::Color(20, 20, 20, 50),
		sf::Color(0, 173, 181, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

AccountSettings::AccountSettings(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states){
	this->initText();
	this->initButtons();
}

AccountSettings::~AccountSettings(){
    auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;
}

void AccountSettings::updateSFMLEvents(){
    while (this->window->pollEvent(this->event)) {
            if (this->event.type == sf::Event::Closed) 
                this->endState();
        }
}

void AccountSettings::updateButtons(){
    for (auto& it : this->buttons)
		it.second->update(this->mousePosView);

	if(this->buttons["CHANGE_EMAIL"]->isPressed()){
		//Change email state
	}

	if(this->buttons["CHANGE_PASSWORD"]->isPressed()){
		//Change pass state
	}

    if (this->buttons["CLOSE"]->isPressed()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		this->states->top()->endState();
	}
}

void AccountSettings::update(){
    this->updateSFMLEvents();
	this->updateMousePositions(this->window);
	this->updateButtons();
}

void AccountSettings::renderText(sf::RenderTarget* target)
{
    target->draw(this->accountSettings);
}

void AccountSettings::renderButtons(sf::RenderTarget* target){
    for (auto& it : this->buttons)
		it.second->render(target);
}

void AccountSettings::render(sf::RenderTarget* target){
    target = this->window;
  
	target->draw(background);

	this->renderText(target);
	this->renderButtons(target);

	this->window->display();
}