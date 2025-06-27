#ifndef NAME_INPUT_SCREEN_H
#define NAME_INPUT_SCREEN_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Screen.h"

namespace sfSnake
{
class NameInputScreen : public Screen
{
public:
    NameInputScreen(std::size_t score);

    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Font font_;
    sf::Text congratsText_;
    sf::Text instructionText_;
    sf::Text nameText_;
    sf::Text cursorText_;
    
    std::string playerName_;
    std::size_t score_;
    bool showCursor_;
    sf::Clock cursorClock_;
    
    void updateDisplay();
};

}

#endif 