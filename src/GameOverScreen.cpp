#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "SettingsScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score)
{
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString("Your score: " + std::to_string(score) + "!"
		"\n\nPress [SPACE] to retry"
		"\n\nPress [S] for settings"
		"\n\nPress [ESC] to quit");
	text_.setCharacterSize(24);
	text_.setColor(sf::Color::Red);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	sf::Event event = Game::Instance->event_;
	if (event.type != sf::Event::KeyReleased) return;
	if (event.key.code == sf::Keyboard::Space)
		Game::Screen = std::make_shared<GameScreen>();
	else if (event.key.code == sf::Keyboard::S)
		Game::Screen = std::make_shared<SettingsScreen>();
	else if (event.key.code == sf::Keyboard::Escape)
		window.close();
}

void GameOverScreen::update(sf::Time delta)
{

}

void GameOverScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
}