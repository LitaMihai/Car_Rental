//#include <SFML/Window.hpp>
#include "AccountUI.h"

AccountUI::AccountUI(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	(this->window).create(sf::VideoMode(width, height), "Auth");
	(this->window).setFramerateLimit(30);
	(this->window).setVerticalSyncEnabled(true);
}
