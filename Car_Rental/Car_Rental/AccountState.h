#pragma once

#include "State.h"
#include "Application.h"

class AccountState : public State
{
private:
	//Variables

	std::string Email;
	std::string Password;
	
	void initVariables();


public:
	//Const - Destr
	AccountState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~AccountState();

	//Functions
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

