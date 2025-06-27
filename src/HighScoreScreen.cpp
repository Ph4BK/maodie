#include <SFML/Graphics.hpp>
#include <memory>
#include <sstream>

#include "HighScoreScreen.h"
#include "MenuScreen.h"
#include "Game.h"
#include "HighScoreManager.h"

using namespace sfSnake;

HighScoreScreen::HighScoreScreen()
{
    font_.loadFromFile("Fonts/game_over.ttf");
    
    titleText_.setFont(font_);
    titleText_.setString("High Scores");
    titleText_.setCharacterSize(48);
    titleText_.setColor(sf::Color::White);
    titleText_.setStyle(sf::Text::Bold);
    
    sf::FloatRect titleBounds = titleText_.getLocalBounds();
    titleText_.setOrigin(titleBounds.left + titleBounds.width / 2,
        titleBounds.top + titleBounds.height / 2);
    titleText_.setPosition(Game::Width / 2, Game::Height / 8);
    
    instructionText_.setFont(font_);
    instructionText_.setString("Press [ESC] to go back");
    instructionText_.setCharacterSize(20);
    instructionText_.setColor(sf::Color::White);
    instructionText_.setPosition(Game::Width / 4, Game::Height * 7 / 8);
    
    // Initialize score texts
    scoreTexts_.resize(HighScoreManager::MAX_SCORES);
    for (size_t i = 0; i < HighScoreManager::MAX_SCORES; ++i)
    {
        scoreTexts_[i].setFont(font_);
        scoreTexts_[i].setCharacterSize(24);
        scoreTexts_[i].setColor(sf::Color::White);
        scoreTexts_[i].setPosition(Game::Width / 4, Game::Height / 4 + i * 30);
    }
    
    updateScoreDisplay();
}

void HighScoreScreen::handleInput(sf::RenderWindow& window)
{
    sf::Event event = Game::Instance->event_;
    if (event.type != sf::Event::KeyReleased) return;
    
    if (event.key.code == sf::Keyboard::Escape)
    {
        Game::Screen = std::make_shared<MenuScreen>();
    }
}

void HighScoreScreen::update(sf::Time delta)
{

}

void HighScoreScreen::render(sf::RenderWindow& window)
{
    if (Game::Instance)
    {
        sf::Color contrastColor = Screen::getContrastColor(Game::Instance->getBackgroundColor());
        titleText_.setColor(contrastColor);
        instructionText_.setColor(contrastColor);
        
        for (auto& scoreText : scoreTexts_)
        {
            scoreText.setColor(contrastColor);
        }
    }
    
    window.draw(titleText_);
    window.draw(instructionText_);
    
    for (const auto& scoreText : scoreTexts_)
    {
        window.draw(scoreText);
    }
}

void HighScoreScreen::updateScoreDisplay()
{
    auto& scoreManager = HighScoreManager::getInstance();
    
    const auto& scores = scoreManager.getTopScores();
    
    for (size_t i = 0; i < HighScoreManager::MAX_SCORES; ++i)
    {
        std::ostringstream oss;
        if (i < scores.size())
        {
            oss << (i + 1) << ". " << scores[i].playerName << " - " << scores[i].score;
        }
        else
        {
            oss << (i + 1) << ". ---";
        }
        scoreTexts_[i].setString(oss.str());
    }
} 