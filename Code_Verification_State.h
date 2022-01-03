#ifndef CODE_VERIFICATION_STATE_H
#define CODE_VERIFICATION_STATE_H

#include "State.h"
#include "Button.h"

class Code_Verification_State : public State{
    private:
        // Variables
        sf::Event event;

        std::map<std::string, Button*> buttons;

        sf::RectangleShape *background;
        sf::Font *font;

        int *code;

        sf::Text codeLabel;
        sf::Text codeText;
        std::string codeInput;

        sf::Text anEmailWasSent;
        sf::Text email;
        sf::Text ifIsRegistrated;
        sf::Text pleaseEnterTheCodeBelow;

        std::string *emailString;

        sf::Clock clock;
	    sf::Time text_effect_time;
	    bool show_cursor;

        // Functions
        void initText();
        void initButtons();

        bool codeVerif(std::string codeInput);

    public:
        // Constructor - Destructor
        Code_Verification_State(sf::RenderWindow* window, std::stack<State*>* states, std::string* emailString);
        virtual ~Code_Verification_State();

        // Functions
        void updateSFMLEvents();
        void updateCursor();
        void updateButtons();
        void update();
        
        void renderText(sf::RenderTarget* target);
        void renderButtons(sf::RenderTarget* target);
        void render(sf::RenderTarget* target = NULL);
};

#endif