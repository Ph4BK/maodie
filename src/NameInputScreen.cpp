#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "NameInputScreen.h"
#include "MenuScreen.h"
#include "Game.h"
#include "HighScoreManager.h"

using namespace sfSnake;

NameInputScreen::NameInputScreen(std::size_t score) 
    : score_(score), showCursor_(true), playerName_("")
{
    font_.loadFromFile("Fonts/game_over.ttf");
    
    congratsText_.setFont(font_);
    if (HighScoreManager::getInstance().isHighestScore(score_)) {
        congratsText_.setString("New record!"
            "\nYou're on the leaderboard!"
            "\nYour score: " + std::to_string(score_));
    } else {
        congratsText_.setString("You're on the leaderboard!"
            "\nYour score: " + std::to_string(score_));
    }
    congratsText_.setCharacterSize(20);
    congratsText_.setColor(sf::Color::Green);
    congratsText_.setStyle(sf::Text::Bold);
    
    sf::FloatRect congratsBounds = congratsText_.getLocalBounds();
    congratsText_.setOrigin(congratsBounds.left + congratsBounds.width / 2,
        congratsBounds.top + congratsBounds.height / 2);
    congratsText_.setPosition(Game::Width / 2, Game::Height / 4);
    
    instructionText_.setFont(font_);
    instructionText_.setString("Enter your name (max 15 characters):"
        "\nPress [ENTER] to submit"
        "\nPress [ESC] to discard");
    instructionText_.setCharacterSize(16);
    instructionText_.setColor(sf::Color::White);
    instructionText_.setPosition(Game::Width / 8, Game::Height / 2);
    
    nameText_.setFont(font_);
    nameText_.setCharacterSize(20);
    nameText_.setColor(sf::Color::White);
    nameText_.setPosition(Game::Width / 8 + 30, Game::Height / 2 + 80);
    
    cursorText_.setFont(font_);
    cursorText_.setString("|");
    cursorText_.setCharacterSize(20);
    cursorText_.setColor(sf::Color::White);
    cursorText_.setPosition(Game::Width / 8 + 30, Game::Height / 2 + 80);
    
    updateDisplay();
}

void NameInputScreen::handleInput(sf::RenderWindow& window)
{   
    sf::Event event = Game::Instance->event_;
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
        Game::Screen = std::make_shared<MenuScreen>();
    
    std::vector<sf::Event> eventQueue = Game::Instance->eventQueue_;
    for (const auto& event : eventQueue) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && !playerName_.empty()) // Backspace
            {
                playerName_.pop_back();
                updateDisplay();
            }
            else if (event.text.unicode == 13) // Enter
            {
                if (!playerName_.empty())
                {
                    auto& scoreManager = HighScoreManager::getInstance();
                    scoreManager.addScore(playerName_, score_);
                    Game::Screen = std::make_shared<MenuScreen>();
                }
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 128 && playerName_.length() < 15)
            {
                playerName_ += static_cast<char>(event.text.unicode);
                updateDisplay();
            }
        }
    }
}

void NameInputScreen::update(sf::Time delta)
{
    // Blink cursor
    if (cursorClock_.getElapsedTime().asSeconds() > 0.5f)
    {
        showCursor_ = !showCursor_;
        cursorClock_.restart();
    }
}

void NameInputScreen::render(sf::RenderWindow& window)
{
    if (Game::Instance)
    {
        sf::Color contrastColor = Screen::getContrastColor(Game::Instance->getBackgroundColor());
        instructionText_.setColor(contrastColor);
        nameText_.setColor(contrastColor);
        cursorText_.setColor(contrastColor);
    }
    
    window.draw(congratsText_);
    window.draw(instructionText_);
    window.draw(nameText_);
    
    if (showCursor_)
    {
        window.draw(cursorText_);
    }
}

void NameInputScreen::updateDisplay()
{
    nameText_.setString(playerName_);
    cursorText_.setPosition(nameText_.getPosition().x + nameText_.getLocalBounds().width, 
                           nameText_.getPosition().y);
} 