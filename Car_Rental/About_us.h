#ifndef ABOUT_US_H
#define ABOUT_US_H

#include "Button.h"

class About_us : public State
{
    private:
        //Variables
        sf::Text title;
        sf::Text paragraph1;
        
        sf::Texture developer;
        sf::Sprite developerSprite;

        sf::Event event;

	    sf::Texture backgroundTexture;
	    sf::RectangleShape background;
	    sf::Font font;

        Button *close;

        // Functions
        void initBackground();
        void initFonts();
        void initText();
        void initImage();
        void initButtons();

    public:
        // Constructor - Destructor
        About_us(sf::RenderWindow* window, std::stack<State*>* states);
        virtual ~About_us();

        // Functions
        void updateSFMLEvents();
        void updateButtons();
        void update();

        void renderText(sf::RenderTarget* target);
        void renderImage(sf::RenderTarget* target);
        void renderButtons(sf::RenderTarget* target);
        void render(sf::RenderTarget* target = NULL);

};

#endif