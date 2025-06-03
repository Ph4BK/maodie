#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{

}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() == 0)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine;
	engine.seed(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Diameter);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Diameter);

	sf::Color color;
	switch (rand() % 8)
	{
		case 0:
			color = sf::Color::Black;
			break;
		case 1:
			color = sf::Color(139, 69, 19); //brown
			break;
		case 2: case 3:
			color = sf::Color::Red;
			break;
		case 4: case 5:
			color = sf::Color::Blue;
			break;
		case 6: case 7:
			color = sf::Color::Green;
			break;
	}
	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), color));
}

