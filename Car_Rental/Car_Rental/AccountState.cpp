#include "AccountState.h"

void AccountState::initVariables()
{
	this->Email = "";
	this->Password = "";
}

AccountState::AccountState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->initVariables();
}

AccountState::~AccountState()
{
	
}

void AccountState::updateInput(const float& dt)
{
}

void AccountState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
}

void AccountState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	//target->draw(this->background);

	//this->renderButtons(target);
}
