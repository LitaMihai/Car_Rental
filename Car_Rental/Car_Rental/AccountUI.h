#pragma once
#include <SFML/Window.hpp>
#include <string>

class AccountUI
{
private:
	//Variables
	unsigned int width;
	unsigned int height;
	sf::Window window;
	std::string Email;
	std::string Password;
	
public:
	//Constructor
	AccountUI(unsigned int width, unsigned int height);
	//Functions
	
};

