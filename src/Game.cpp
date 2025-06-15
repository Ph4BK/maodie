#include <SFML/Graphics.hpp>

#include <memory>

#include "MenuScreen.h"
#include "Game.h"
#include "SnakeNode.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();
std::unique_ptr<Game> Game::Instance = nullptr;

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake"), backgroundColor_(sf::Color::Black), gridColor_(sf::Color::Transparent)
{
	Instance = std::unique_ptr<Game>(this);
	bgMusic_.openFromFile("Music/bg_music.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}

void Game::handleInput()
{
	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

void Game::render()
{
	window_.clear(backgroundColor_);
	
	// Draw grid if gridColor_ is not transparent
	if (gridColor_.a > 0)
	{
		sf::RectangleShape line;
		line.setFillColor(gridColor_);
		
		// Draw vertical lines
		for (int x = 0; x <= Width; x += static_cast<int>(SnakeNode::Diameter))
		{
			line.setSize(sf::Vector2f(1, Height));
			line.setPosition(x, 0);
			window_.draw(line);
		}
		
		// Draw horizontal lines
		for (int y = 0; y <= Height; y += static_cast<int>(SnakeNode::Diameter))
		{
			line.setSize(sf::Vector2f(Width, 1));
			line.setPosition(0, y);
			window_.draw(line);
		}
	}
	
	Game::Screen->render(window_);
	window_.display();
}

void Game::getEvent(sf::RenderWindow& window)
{
	event_ = sf::Event();
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			return;
		}
		else if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased)
		    event_ = event;
	}
}

void Game::setBackgroundColor(const sf::Color& color)
{
	backgroundColor_ = color;
}

sf::Color Game::getBackgroundColor() const
{
	return backgroundColor_;
}

void Game::setGridColor(const sf::Color& color)
{
	gridColor_ = color;
}

sf::Color Game::getGridColor() const
{
	return gridColor_;
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			getEvent(window_);
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}