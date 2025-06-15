#include <SFML/Graphics.hpp>
#include <memory>

#include "SettingsScreen.h"
#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

SettingsScreen::SettingsScreen() : selectedColorIndex_(0), selectedGridIndex_(0), currentSelection_(0)
{   
    font_.loadFromFile("Fonts/game_over.ttf");
	
	titleText_.setFont(font_);
	titleText_.setString("Settings");
	titleText_.setCharacterSize(48);
	titleText_.setColor(sf::Color::White);
	titleText_.setStyle(sf::Text::Bold);
	
	sf::FloatRect titleBounds = titleText_.getLocalBounds();
	titleText_.setOrigin(titleBounds.left + titleBounds.width / 2,
		titleBounds.top + titleBounds.height / 2);
	titleText_.setPosition(Game::Width / 2, Game::Height / 8);
	
	instructionText_.setFont(font_);
	instructionText_.setString(
        "Use arrows to navigate"
        "\nPress [ESC] to go back");
	instructionText_.setCharacterSize(16);
	instructionText_.setColor(sf::Color::White);
	instructionText_.setPosition(Game::Width / 8, Game::Height / 4);
	
    backgroundText_.setFont(font_);
    backgroundText_.setString("Background Color:");
    backgroundText_.setCharacterSize(20);
    backgroundText_.setColor(sf::Color::White);
    backgroundText_.setStyle(sf::Text::Bold);
    backgroundText_.setPosition(Game::Width / 8, Game::Height / 2);

	gridText_.setFont(font_);
	gridText_.setString("Grid Color:");
	gridText_.setCharacterSize(20);
	gridText_.setColor(sf::Color::White);
	gridText_.setPosition(Game::Width / 8, Game::Height * 3 / 4);

	colors_ = {
        sf::Color::Black,
		sf::Color::White,
		sf::Color(139, 69, 19), // Brown
	};
	
	colorNames_ = {
        "Black",
		"White",
		"Brown",
	};

	gridColors_ = {
		sf::Color::Transparent,
		sf::Color::Black,
		sf::Color::White,
		sf::Color(139, 69, 19), // Brown
	};

	gridColorNames_ = {
		"None",
		"Black", 
		"White",
		"Brown",
	};
	
	colorOptions_.resize(colors_.size());
	for (size_t i = 0; i < colors_.size(); ++i)
	{
		colorOptions_[i].setFont(font_);
		colorOptions_[i].setString(colorNames_[i]);
		colorOptions_[i].setCharacterSize(20);
		colorOptions_[i].setPosition(Game::Width * (1 + i) / 5, Game::Height * 5 / 8);
	}

	gridOptions_.resize(gridColors_.size());
	for (size_t i = 0; i < gridColors_.size(); ++i)
	{
		gridOptions_[i].setFont(font_);
		gridOptions_[i].setString(gridColorNames_[i]);
		gridOptions_[i].setCharacterSize(20);
		gridOptions_[i].setPosition(Game::Width * (1 + i) / 5, Game::Height * 7 / 8);
	}
	
	updateColorSelection();
	updateGridSelection();
	updateCurrentSelection();
}

void SettingsScreen::handleInput(sf::RenderWindow& window)
{
    sf::Event event = Game::Instance->event_;
    if (event.type != sf::Event::KeyReleased) return;
    
    if (event.key.code == sf::Keyboard::Up)
    {
        currentSelection_ = 0;
        updateCurrentSelection();
    }
    else if (event.key.code == sf::Keyboard::Down)
    {
        currentSelection_ = 1;
        updateCurrentSelection();
    }
    else if (event.key.code == sf::Keyboard::Left)
    {
        if (currentSelection_ == 0)
        {
            selectedColorIndex_ = (selectedColorIndex_ - 1 + colors_.size()) % colors_.size();
            updateColorSelection();
            Game::Instance->setBackgroundColor(colors_[selectedColorIndex_]);
        }
        else if (currentSelection_ == 1)
        {
            selectedGridIndex_ = (selectedGridIndex_ - 1 + gridColors_.size()) % gridColors_.size();
            updateGridSelection();
            Game::Instance->setGridColor(gridColors_[selectedGridIndex_]);
        }
    }
    else if (event.key.code == sf::Keyboard::Right)
    {
        if (currentSelection_ == 0)
        {
            selectedColorIndex_ = (selectedColorIndex_ + 1) % colors_.size();
            updateColorSelection();
            Game::Instance->setBackgroundColor(colors_[selectedColorIndex_]);
        }
        else if (currentSelection_ == 1)
        {
            selectedGridIndex_ = (selectedGridIndex_ + 1) % gridColors_.size();
            updateGridSelection();
            Game::Instance->setGridColor(gridColors_[selectedGridIndex_]);
        }
    }
    else if (event.key.code == sf::Keyboard::Escape)
    {
        Game::Screen = std::make_shared<MenuScreen>();
    }
}

void SettingsScreen::update(sf::Time delta)
{

}

void SettingsScreen::render(sf::RenderWindow& window)
{
	if (Game::Instance)
	{
		sf::Color contrastColor = Screen::getContrastColor(Game::Instance->getBackgroundColor());
		titleText_.setColor(contrastColor);
		instructionText_.setColor(contrastColor);
		backgroundText_.setColor(contrastColor);
		
		for (size_t i = 0; i < colorOptions_.size(); ++i)
			colorOptions_[i].setColor(contrastColor);

		gridText_.setColor(contrastColor);
		
		for (size_t i = 0; i < gridOptions_.size(); ++i)
			gridOptions_[i].setColor(contrastColor);
	}
	
	window.draw(titleText_);
	window.draw(instructionText_);
    window.draw(backgroundText_);
	window.draw(gridText_);
	
	for (const auto& colorOption : colorOptions_)
	{
		window.draw(colorOption);
	}

	for (const auto& gridOption : gridOptions_)
	{
		window.draw(gridOption);
	}
}

void SettingsScreen::updateColorSelection()
{
	for (size_t i = 0; i < colorOptions_.size(); ++i)
	{   
        colorOptions_[i].setColor(sf::Color::White);
		if (i == selectedColorIndex_)
            colorOptions_[i].setString(">" + colorNames_[i] + "<");
		else
            colorOptions_[i].setString(" " + colorNames_[i] + " ");
	}
}

void SettingsScreen::updateGridSelection()
{
	for (size_t i = 0; i < gridOptions_.size(); ++i)
	{   
        gridOptions_[i].setColor(sf::Color::White);
		if (i == selectedGridIndex_)
            gridOptions_[i].setString(">" + gridColorNames_[i] + "<");
		else
            gridOptions_[i].setString(" " + gridColorNames_[i] + " ");
	}
}

void SettingsScreen::updateCurrentSelection()
{
	if (currentSelection_ == 0) {
		backgroundText_.setStyle(sf::Text::Bold);
		gridText_.setStyle(sf::Text::Regular);
	}
	else if (currentSelection_ == 1) {
		backgroundText_.setStyle(sf::Text::Regular);
		gridText_.setStyle(sf::Text::Bold);
	}
} 