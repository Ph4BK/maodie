#ifndef HIGH_SCORE_SCREEN_H
#define HIGH_SCORE_SCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Screen.h"

namespace sfSnake
{
class HighScoreScreen : public Screen
{
public:
    HighScoreScreen();

    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Font font_;
    sf::Text titleText_;
    sf::Text instructionText_;
    std::vector<sf::Text> scoreTexts_;
    
    void updateScoreDisplay();
};

}

#endif 