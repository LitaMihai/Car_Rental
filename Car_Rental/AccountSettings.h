#ifndef ACCOUNT_SETTINGS_H
#define ACCOUNT_SETTINGS_H

#include "State.h"
#include "Button.h"
#include "Code_Verification_State.h"


class AccountSettings : public State{
    private:
        // Variables
        std::map<std::string, Button*> buttons;

        sf::Text accountSettings;

        sf::Event event;

        // Functions
	    void initBackground();
	    void initFonts();
        void initText();
	    void initButtons();

    public:
        // Constructor - Destructor
        AccountSettings(sf::RenderWindow* window, std::stack<State*>* states);
        virtual ~AccountSettings();

        // Functions
        void updateSFMLEvents();
        void updateButtons();
        void update();

        void renderText(sf::RenderTarget* target);
        void renderButtons(sf::RenderTarget* target = NULL);
        void render(sf::RenderTarget* target = NULL);
};

#endif